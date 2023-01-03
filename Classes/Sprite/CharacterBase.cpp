#include "CharacterBase.h"
#include "Skill/SkillBase.h"
#include "Skill/Defense.h"
#include "Skill/SpeedUp.h"
#include <iostream>

bool CharacterBase::init(int tag, MapBase* map)
{
    if (!Sprite::init())
        return false;

    this->setTag(tag);

    this->map = map;
    accelerate = 0;
    x_speed = 0;
    y_speed = 0;
    defense = false;
    isDoubleJump = false;
    inTheAir = true;
    floor = map->Floor.size() - 1;
    
    float x = GameManager::Random(int(map->Floor.back().front()), int(map->Floor.back().back()));
    while(!InTheBoundary(map->Floor.back(),x))
        x = GameManager::Random(int(map->Floor.back().front()), int(map->Floor.back().back()));

    this->setPosition(x,map->platform->getContentSize().height + 2000);

    skill = new Defense(this, 3);

    this->scheduleUpdate();

	return true;
}

Sprite* CharacterBase::clone()
{
    Sprite* _body = Sprite::createWithSpriteFrameName(body->name);
    Sprite* _head = Sprite::createWithSpriteFrameName(head->name);
    Sprite* _hand1 = Sprite::createWithSpriteFrameName(hand1->name);
    Sprite* _hand2 = Sprite::createWithSpriteFrameName(hand2->name);
    Sprite* _foot1 = Sprite::createWithSpriteFrameName(feet1->name);
    Sprite* _foot2 = Sprite::createWithSpriteFrameName(feet2->name);
    Sprite* _face = Sprite::createWithSpriteFrameName(face->name);
    Sprite* _gun_right = gun->RightGun();
    Sprite* _gun_left = gun->LeftGun();
    if (gun->change) {
        _gun_right = nullptr;
        _gun_left = nullptr;
    }

    _body->setFlippedX(body->isFlippedX());
    _head->setFlippedX(head->isFlippedX());
    _hand1->setFlippedX(hand1->isFlippedX());
    _hand2->setFlippedX(hand2->isFlippedX());
    _foot1->setFlippedX(feet1->isFlippedX());
    _foot2->setFlippedX(feet2->isFlippedX());
    _face->setFlippedX(face->isFlippedX());
    if(_gun_right)_gun_right->setFlippedX(gun->isFlippedX());
    if(_gun_left)_gun_left->setFlippedX(gun->isFlippedX());


    _foot1->setAnchorPoint(feet1->organ->getAnchorPoint());
    _foot2->setAnchorPoint(feet2->organ->getAnchorPoint());
    _face->setAnchorPoint(face->organ->getAnchorPoint());
    if(_gun_right)_gun_right->setAnchorPoint(gun->gun_right->getAnchorPoint());
    if(_gun_left)_gun_left->setAnchorPoint(gun->gun_left->getAnchorPoint());

    _foot1->setRotation(feet1->organ->getRotation());
    _foot2->setRotation(feet2->organ->getRotation());
    if(_gun_right)_gun_right->setRotation(gun->gun_right->getRotation());
    if(_gun_left)_gun_left->setRotation(gun->gun_left->getRotation());

    Vec2 origin = _body->getContentSize() / 2;

    _head->setPosition(head->getPosition() + head->organ->getPosition() + origin);
    _hand1->setPosition(hand1->getPosition() + hand1->organ->getPosition() + origin);
    _hand2->setPosition(hand2->getPosition() + hand2->organ->getPosition() + origin);
    _foot1->setPosition(feet1->getPosition() + feet1->organ->getPosition() + origin);
    _foot2->setPosition(feet2->getPosition() + feet2->organ->getPosition() + origin);
    _face->setPosition(face->getPosition() + face->organ->getPosition() + _head->getContentSize() / 2);
    if(_gun_right)_gun_right->setPosition(gun->gun_right->getPosition());
    if (_gun_left)_gun_left->setPosition(gun->gun_left->getPosition());

    _body->addChild(_head, 1);
    _body->addChild(_hand1, 1);
    _body->addChild(_hand2, -1);
    _body->addChild(_foot1, 1);
    _body->addChild(_foot2, -1);
    _head->addChild(_face, 1);
    if(_gun_right)_hand1->addChild(_gun_right, -1);
    if (_gun_left)_hand2->addChild(_gun_left, 1);

    _body->retain();

    return _body;
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
    gun->update(dt);

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
                DustUpdate();
                keyMap["up"] = false;
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
            if (std::abs(y_speed) <= std::abs(status->gravitation * dt) && status->gravitation < 0)
                MoveDelay(false, false);
            if (!isDoubleJump && keyMap["up"]) {
                y_speed = status->y_maxSpeed / 1.2;
                MoveDelay(true, false);
                isDoubleJump = true;
                DrawHalo();
                keyMap["up"] = false;
            }
            y_speed += status->gravitation * dt;
            if (y_speed < -status->y_maxSpeed * 2.5)
                y_speed = -status->y_maxSpeed * 2.5;
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
                DustUpdate();
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
                if (skill) { delete skill; skill = nullptr; }
                });
            CallFunc* func2 = CallFunc::create([&]() {
                skill = new Defense(this, 3);
                this->setVisible(true); valid = true;
                });
            float x = GameManager::Random(int(map->Floor.back().front()), int(map->Floor.back().back()));
            while (!InTheBoundary(map->Floor.back(), x))
                x = GameManager::Random(int(map->Floor.back().front()), int(map->Floor.back().back()));
            Vec2 position = Vec2(x, map->platform->getContentSize().height + 2000);
            auto move1 = MoveTo::create(0.5, position);
            auto move2 = EaseSineOut::create(move1);
            this->runAction(Sequence::create(func1, move2, func2, nullptr));
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
                    hand1->RaiseHandToShoot(map,true);//true代表右手
                    hand2->RaiseHandToShoot(map,false);//false代表左手

                    this->_flippedX ? x_speed += gun->recoilSpeed : x_speed -= gun->recoilSpeed;
                    if (std::abs(x_speed) > status->x_maxSpeed)
                        this->_flippedX ? x_speed -= gun->recoilSpeed : x_speed += gun->recoilSpeed;
                }
            }
        }
        if (gun->bulletCount >= gun->bulletClip && gun->deltatime > gun->shotInterval) {
            throwGun = gun->clone();
            GunChange(initGun);
            hand1->BulletChangeWithHand(throwGun, true);
            hand2->BulletChangeWithHand(throwGun, false);
        }

        if (skill) {
            if (skill->duration > skill->Duration) {
                delete skill;
                skill = nullptr;
            }
            else {
                skill->update(dt);
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
    if(gun->gunshadow_right) gun->gunshadow_right->removeFromParent();
    if (gun->gunshadow_left) gun->gunshadow_left->removeFromParent();
    if(gun->gun_right)gun->gun_right->removeFromParent();
    if (gun->gun_left)gun->gun_left->removeFromParent();
    gun = change->clone();

    Vec2 left = hand1->initPosition;
    Vec2 right = hand2->initPosition;
    if (flip) { left.x = -left.x; right.x = -right.x; }
    hand1->setPosition(left);
    hand2->setPosition(right);

    if(gun->gun_right)gun->setFlippedX(gun->gun_right,flip,true, hand1->organ->getContentSize().width);
    if (gun->gun_left)gun->setFlippedX(gun->gun_left, flip,false, hand1->organ->getContentSize().width);

    gun->map = this->map;
    hand1->GetGun(gun,true);
    hand2->GetGun(gun,false);
    gun->player = this;
    if(onaction){
        //CCLOG("yes");
        hand1->DelayWithHand(true);
        hand2->DelayWithHand(false);
    }
}

void CharacterBase::GetOpponent(CharacterBase* opponent)
{
    this->opponent = opponent;
}

void CharacterBase::DustUpdate()
{
    for (auto& dust : dusts) {
        if (dust->dissipate == dust->Dusts.size()) {
            dust->removeFromParent();
            dust = nullptr;
        }
    }
    std::vector<Dust*> temp;
    for (auto dust : dusts) {
        if (dust)
            temp.push_back(dust);
    }
    dusts = temp;
    dusts.push_back(Dust::create(map, this->getPosition()));
}
