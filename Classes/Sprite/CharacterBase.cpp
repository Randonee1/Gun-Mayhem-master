#include "CharacterBase.h"
#include <iostream>

bool CharacterBase::init(MapBase* map)
{
    if (!Sprite::init())
        return false;

    this->map = map;
    accelerate = 0;
    x_speed = 0;
    y_speed = 0;
    isDoubleJump = false;
    inTheAir = true;

    this->scheduleUpdate();

	return true;
}

bool CharacterBase::InTheBoundary(std::vector<float>& floor, float x) const
{
    for (int i = 0; i < floor.size() - 1; i += 2) {
        if (x > floor[i] && x < floor[i + 1])
            return true;
    }
    return false;
}

void CharacterBase::update(float dt)
{
	Sprite::update(dt);
    if(valid)
    {
        if (keyMap["skill"]) {

        }

        if (!inTheAir) {
            y_speed = 0;
            isDoubleJump = false;
            if (!InTheBoundary(map->Floor[floor],getPositionX())) {
                keyMap["down"] = true;
                inTheAir = true;
                if (floor > 0)
                    floor--;
            }
            else if (keyMap["up"]) {
                inTheAir = true;
                y_speed = status->y_maxSpeed;
                MoveDelay(true, false);
                keyMap["up"] = false;
               /* if (floor < map->Floor.size() - 1)
                    floor++;*/
            }
            else if (keyMap["down"]) {
                if (floor > 0) {
                    inTheAir = true;
                    floor--;
                }
            }

        }
        if (inTheAir) {
            //跳起暂停走路动作
            StopWalk();
            if (std::abs(y_speed) <= std::abs(status->gravitation * dt))
                MoveDelay(false, false);
            if (!isDoubleJump && keyMap["up"]) {
                /*if (keyMap["down"] && floor < map->Floor.size() - 1)
                    floor++;
                if (getPositionY() > map->floor_base + floor * map->floor_height && floor < map->Floor.size() - 1)
                    floor++;*/
                y_speed = status->y_maxSpeed / 1.2;
                MoveDelay(true, false);
                isDoubleJump = true;
                DrawHalo();
            }
            y_speed += status->gravitation * dt;
            if (y_speed < -status->y_maxSpeed * 2.5)
                y_speed = -status->y_maxSpeed * 2.5;
            keyMap["up"] = false;
        }
        if (y_speed > 0) {
            if (getPositionY() + y_speed * dt > map->floor_base + floor * map->floor_height &&
                floor < map->Floor.size() - 1)
                floor++;
        }
        if (y_speed < 0)
        {
            if (getPositionY() > map->floor_base + floor * map->floor_height &&
                getPositionY() + y_speed * dt < map->floor_base + floor * map->floor_height &&
                InTheBoundary(map->Floor[floor], getPositionX())) {
                keyMap["down"] = false;
                MoveDelay(true, true);
                inTheAir = false;
                y_speed = 0;
                this->setPositionY(map->floor_base + floor * map->floor_height);
            }
            else {
                this->setPositionY(getPositionY() + y_speed * dt);
                if (getPositionY() < map->floor_base + floor * map->floor_height && floor > 0)
                    floor--;
            }
        }
        else
            this->setPositionY(getPositionY() + y_speed * dt);

        if (getPositionY() < map->death_line)
        {
            GunChange(initGun->clone());

            CallFunc* func1 = CallFunc::create([&]() {
                this->setVisible(false); this->Flip(false);
                y_speed = 0; x_speed = 0; valid = false; floor = map->Floor.size() - 1;
                });
            CallFunc* func2 = CallFunc::create([&]() {
                
                this->setVisible(true); valid = true;
                });
            unsigned seed = time(0);
            Vec2 position = Vec2(rand() % int(map->platform->getContentSize().width / 2) + map->platform->getContentSize().width / 4,
                map->platform->getContentSize().height + 2000);
            auto move1 = MoveTo::create(0.5, position);
            auto move2 = EaseSineOut::create(move1);
            this->runAction(Sequence::create(func1, move2, func2, nullptr));
            /*y_speed = 0;
            floor = map->Floor.size() - 1;
            setPosition(initPosition);*/
        }


        if ((keyMap["left"] ^ keyMap["right"])) {

            if (keyMap["left"])
                Flip(true);
            else
                Flip(false);

            accelerate = keyMap["right"] ? status->acceleration : -status->acceleration;
            if (!inTheAir) {
                feet1->Walk(false);
                feet2->Walk(true);
                hand1->Walk(true);
                hand2->Walk(false);

            }
            x_speed += accelerate * dt;
            if (x_speed * accelerate > 0 && std::abs(x_speed) > status->x_maxSpeed )
                x_speed -= accelerate * dt;
        }
        else if(! inTheAir) {
            accelerate = x_speed > 0 ? -status->resistance : status->resistance;
            if (std::abs(accelerate * dt) > std::abs(x_speed))
                x_speed = 0;
            else
                x_speed += accelerate * dt;
        }
        this->setPositionX(getPositionX() + x_speed * dt);
  
        if (gun->isGatling) {
            CCLOG("yes");
            Vec2 left = hand1->isFlippedX() ? Vec2(29, 0) : Vec2(-29, 0);
            Vec2 right = hand2->isFlippedX() ? Vec2(-75, 5) : Vec2(75, 5);
            hand1->organ->stopActionByTag(10);
            hand2->organ->stopActionByTag(10);
            hand1->setPosition(left);
            hand2->setPosition(right);
        }

        if (keyMap["shot"]) {
            
            if(gun->shot) {
                if(!gun->change){
                    hand1->RaiseHandToShoot(map,gun,true);
                    hand2->RaiseHandToShoot(map,gun,false);
                    this->_flippedX ? x_speed += gun->recoilSpeed : x_speed -= gun->recoilSpeed;
                    /*if (std::abs(x_speed) > status->x_maxSpeed)
                        this->_flippedX ? x_speed = status->x_maxSpeed : x_speed = -status->x_maxSpeed;*/
                }
            }
            if (gun->bulletCount > gun->bulletClip) {
                throwGun = gun->clone();
                GunChange(initGun);
                hand1->BulletChangeWithHand(gun, throwGun,true);
                hand2->BulletChangeWithHand(gun, throwGun,false);
            }
        }
        
    }
}

void CharacterBase::MoveDelay(bool up, bool floor)
{
    for (int i = 2; i < organs.size(); i++)
        organs[i]->MoveDelay(up, floor);
}

void CharacterBase::Flip(bool direction)
{
    this->setFlippedX(direction);
    for (auto organ : organs)
        organ->setFlippedX(direction);
}

void CharacterBase::StopWalk()
{
    feet1->organ->stopActionByTag(10);
    feet2->organ->stopActionByTag(10);
    feet1->actionState = false;
    feet2->actionState = false;
    hand1->organ->stopActionByTag(10);
    hand2->organ->stopActionByTag(10);
    hand1->actionState = false;
    hand2->actionState = false;
}

void CharacterBase::DrawHalo()
{
    Sprite* hole = Sprite::createWithSpriteFrameName("jump_halo.png");
    hole->setPosition(this->getPosition() - Vec2(0, 80));
    map->platform->addChild(hole, 4);
    auto scale = ScaleTo::create(0.5, 0.1);
    auto fadeout = FadeOut::create(0.5);
    auto spa = Spawn::create(scale, fadeout, nullptr);
    hole->runAction(spa);
}

void CharacterBase::GunChange(GunBase* change)
{
    bool flip = gun->isFlippedX();
    bool onaction = gun->onShot;
    float angle = gun->gun->getRotation();
    if(gun->gunshadow)
        gun->gunshadow->removeFromParent();
    gun->removeFromParent();
    gun = change->clone();

    Vec2 left = hand1->initPosition;
    Vec2 right = hand2->initPosition;
    if (flip) { left.x = -left.x; right.x = -right.x; }
    hand1->setPosition(left);
    hand2->setPosition(right);

    gun->setFlippedX(flip, hand1->organ->getContentSize().width);
    gun->map = this->map;
    hand1->GetGun(gun);
    if(onaction){
        gun->gun->setRotation(angle);
        hand1->DelayWithHand(gun,true);
        hand2->DelayWithHand(gun, false);
    }
}

void CharacterBase::GetOpponent(CharacterBase* opponent)
{
    this->opponent = opponent;
}
