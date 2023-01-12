#include "GunBase.h"
#include "Organ/hand.h"
#include "Sprite/CharacterBase.h"

bool GunBase::init()
{
    if (!Sprite::init()) {
        return false;
    }
    /*gun->setAnchorPoint(Vec2(0.2, 0.25));
    gun->setRotation(30.0f);*/
    this->scheduleUpdate();

    return true;
}

GunBase* GunBase::clone()
{
    return nullptr;
}

Sprite* GunBase::RightGun()
{
    return nullptr;
}

Sprite* GunBase::LeftGun()
{
    return nullptr;
}

void GunBase::setFlippedX(Sprite* gun, bool flippedX, bool right, float offset)
{
    bool flip = gun->isFlippedX();
    gun->setFlippedX(flippedX);
    if (flip != flippedX)
    {
        _flippedX = flippedX;
        gun->setPositionX(-gun->getPositionX() + offset);
        Vec2 anch = right? anchor : anchor_left;
        flippedX ? anch.x = 1 - anchor.x : anch.x = anchor.x;
        gun->setAnchorPoint(anch);
        /*if (!onShot)
            flippedX ? gun->setRotation(-initRotation) : gun->setRotation(initRotation);*/
        gun->setRotation(-gun->getRotation());

    }
}

void GunBase::Shot(MapBase* map, bool right)
{
    onShot = false;
    this->map = map;
    if(gun_right && right) gun_right->stopAllActions();
    if (gun_left && !right) gun_left->stopAllActions();
    
    //bulletCount++;
    shot = false;
    deltatime = 0;
}

void GunBase::Change(GunBase* throwgun, bool withgun)
{
    onShot = false;
    if(gun_right) gun_right->stopAllActions();
    if (gun_left) gun_left->stopAllActions();

    deltatime = 0;
    bulletCount = 0;

}

void GunBase::Delay(bool right)
{
    return;
}

Sequence* GunBase::RaiseHand(bool withgun)
{
    return nullptr;
}



Sequence* GunBase::BulletChange(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = MoveTo::create(0.3, Vec2(0, 0));
    if (withgun) {
        auto throwaway = EaseSineOut::create(MoveTo::create(0.15, Vec2(120, 64)));
        auto movedown = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
        auto moveup = EaseSineOut::create(MoveTo::create(0.3, Vec2(70, 14)));
        return Sequence::create(throwaway, movedown, moveup, delay, down, nullptr);
    }
    else {
        auto throwaway = EaseSineOut::create(MoveTo::create(0.15, Vec2(15, -5)));
        auto movedown = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
        auto moveup = EaseSineOut::create(MoveTo::create(0.3, Vec2(15, -5)));
        return Sequence::create(throwaway, movedown, moveup, delay, down, nullptr);
    }
}

Sequence* GunBase::HoldingOn(bool withgun)
{
    return nullptr;
}

void GunBase::SetBullet()
{
    bulletCount++;
}

void GunBase::SetBulletCase()
{
    return;
}

void GunBase::SetShot()
{
    onShot = !onShot;
}

void GunBase::update(float dt)
{
    deltatime += dt;
    if (deltatime < shotInterval && bulletCount!=0) {
        shot = false;
    }
    else if (bulletCount > bulletClip) {
        shot = false;
    }
    else {
        shot = true;
    }
}

Vec2 GunBase::GetPositionToBackground(bool right)
{
    auto gun = gun_right ? gun_right : gun_left;

    auto player = gun->getParent()->getParent()->getParent();
    auto hand = right ? player->getChildByTag(1) : player->getChildByTag(2);
    auto hand_organ = hand->getChildren().front();
   
    Vec2 hand_organ_position = hand_organ->getPosition();
    Vec2 hand_position = hand->getPosition();
    Vec2 player_position = player->getPosition();

    return hand_organ_position + hand_position + player_position;
}
