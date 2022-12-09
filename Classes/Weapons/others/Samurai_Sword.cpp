#include "Samurai_Sword.h"
#include "Sprite/CharacterBase.h"

Sanurai_Sword* Sanurai_Sword::create()
{
    auto sword = new Sanurai_Sword();
    if (sword && sword->init()) {
        return sword;
    }
    CC_SAFE_DELETE(sword);
    return NULL;
}

Sanurai_Sword* Sanurai_Sword::clone()
{
    return Sanurai_Sword::create();
}

Sprite* Sanurai_Sword::RightGun()
{
    return Sprite::create("samurai_sword.png");
}

bool Sanurai_Sword::init()
{
    if (!GunBase::init())
        return false;

    gun_right = Sprite::create("samurai_sword.png");
   

    anchor = Vec2(0.2, 0.5);
    initRotation = -25.0f;
    shotInterval = 0.53;
    bulletClip = INT_MAX;
    bulletCount = 0;

    gun_right->setAnchorPoint(anchor);
    gun_right->setRotation(initRotation);
    return true;
}

void Sanurai_Sword::Shot(MapBase* map, bool right)
{
    GunBase::Shot(map, right);
    gun_right->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* onsword = CallFunc::create([&]() {onSword = !onSword; hit = false; });
    CallFunc* jump = CallFunc::create(CC_CALLBACK_0(Sanurai_Sword::Jump, this));
    CallFunc* Chop = CallFunc::create([&]() {chop = !chop; });
    auto aim1 = RotateTo::create(0, -150);
    auto rotate1 = RotateTo::create(0.03, 80);
    auto rotate2 = RotateTo::create(0.05, -50);
    auto rotate3 = RotateTo::create(0.05, -110);
    auto rotate_delay = RotateTo::create(0.2, -110);
    auto back = RotateTo::create(0.2, initRotation);
    auto seq_shot = Sequence::create(onshot, onsword, aim1, rotate1,Chop,jump, rotate2,Chop, rotate3,rotate_delay,onsword, back, onshot, nullptr);
    gun_right->runAction(seq_shot);
}

Sequence* Sanurai_Sword::RaiseHand(bool withgun)
{
    auto move1 = EaseSineOut::create(MoveBy::create(0.03, Vec2(50, 10)));
    auto move2 = EaseSineOut::create(MoveBy::create(0.10, Vec2(40, 70)));
    auto move_delay = MoveBy::create(0.2, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.2, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(0,0));
        return Sequence::create(raise, move1,move2,move_delay, down, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(-63, -40));
       
        return Sequence::create(raise, move1,move2, move_delay, down, nullptr);
    }
}

void Sanurai_Sword::Delay(bool right)
{
    return;
}

Sequence* Sanurai_Sword::HoldingOn(bool withgun)
{
    return Sequence::create(MoveTo::create(0,Vec2(0, 0)), nullptr);
}

void Sanurai_Sword::update(float dt)
{
    if (!player->inTheAir)
        isSwing = false;

    deltatime += dt;
    if (deltatime < shotInterval || isSwing) {
        shot = false;
    }
    else {
        shot = true;
    }

    if (chop) {
        auto rect_sword = gun_right->getBoundingBox();
        Vec2 offset_sword = player->getPosition() + player->hand1->getPosition();
        rect_sword.origin += offset_sword;
        auto rect_opponent = player->opponent->body->organ->getBoundingBox();
        Vec2 offset_opponent = player->opponent->getPosition() + player->opponent->body->getPosition();
        rect_opponent.origin += offset_opponent;
        if (rect_opponent.intersectsRect(rect_sword) &&!player->opponent->defense&& !hit &&
            ((player->opponent->getPositionX()-player->getPositionX()>0 && !this->isFlippedX()) || 
             (player->opponent->getPositionX() - player->getPositionX() < 0 && this->isFlippedX()))) {
            player->opponent->x_speed = this->isFlippedX() ? -1000+player->x_speed : 1000+player->x_speed;
            player->opponent->y_speed = 1500;
            player->opponent->inTheAir = true;
            player->opponent->MoveDelay(true, false);

            auto blood = Blood::create();
            blood->setPosition((offset_sword + 3*offset_opponent)/4);
            player->map->platform->addChild(blood, 4);

            hit = true;
        }
    }
}

void Sanurai_Sword::Jump()
{
    isSwing = true;
    player->inTheAir = true;
    player->y_speed = player->status->y_maxSpeed / 1.2; 
    player->MoveDelay(true, false);
}
