#include "GunBase.h"

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

Sprite* GunBase::ThrowGun()
{
    return nullptr;
}

//GunBase* GunBase::CreateWithName(const char* name)
//{
//    auto gun = new GunBase();
//    if (gun && gun->initWithName(name)) {
//        gun->autorelease();
//        return gun;
//    }
//    CC_SAFE_DELETE(gun);
//    return NULL;
//}

void GunBase::setFlippedX(bool flippedX,float offset)
{
    gun->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        this->setPositionX(-this->getPositionX()+offset);
        flipX();
        Vec2 anch = anchor;
        flippedX ? anch.x = 1 - anchor.x : anch.x = anchor.x;
        gun->setAnchorPoint(anch);
        if(!onShot)
            flippedX ? gun->setRotation(-initRotation) : gun->setRotation(initRotation);
    }
}

void GunBase::setFlippedX(Sprite* gun, bool flippedX, float offset)
{
    gun->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        gun->setPositionX(-gun->getPositionX() + offset);
        Vec2 anch = anchor;
        flippedX ? anch.x = 1 - anchor.x : anch.x = anchor.x;
        gun->setAnchorPoint(anch);
        if (!onShot)
            flippedX ? gun->setRotation(-initRotation) : gun->setRotation(initRotation);
    }
}

void GunBase::Shot(MapBase* map)
{
    onShot = false;
    this->map = map;
    gun->stopAllActions();
    
    bulletCount++;
    shot = false;
    deltatime = 0;
}

void GunBase::Change(GunBase* throwgun, bool withgun)
{
    onShot = false;
    gun->stopAllActions();

    deltatime = 0;
    bulletCount = 0;

}

void GunBase::Delay()
{
    return;
}

Sequence* GunBase::RaiseHand(bool withgun)
{
    return nullptr;
}



Sequence* GunBase::BulletChange(bool withgun)
{
    return nullptr;
}

Sequence* GunBase::HoldingOn(bool withgun)
{
    return nullptr;
}

void GunBase::SetBullet()
{
    return;
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

Vec2 GunBase::GetPositionToBackground(int tag)
{
    auto player = this->getParent()->getParent()->getParent();
    auto hand = player->getChildByTag(tag);
    Vec2 hand_organ_position = this->getParent()->getPosition();
    Vec2 hand_position = hand->getPosition();
    Vec2 player_position = player->getPosition();

    return hand_organ_position + hand_position + player_position;
}
