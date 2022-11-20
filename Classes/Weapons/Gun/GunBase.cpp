#include "GunBase.h"

bool GunBase::initWithName(const char* name)
{
    if (!Sprite::init()) {
        return false;
    }
    gun = Sprite::create(name);
    gun->setAnchorPoint(Vec2(0.2, 0.25));
    gun->setRotation(30.0f);
    this->addChild(gun, 0);
}

GunBase* GunBase::CreateWithName(const char* name)
{
    auto gun = new GunBase();
    if (gun && gun->initWithName(name)) {
        gun->autorelease();
        return gun;
    }
    CC_SAFE_DELETE(gun);
    return NULL;
}

void GunBase::setFlippedX(bool flippedX,float offset)
{
    gun->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        this->setPositionX(-this->getPositionX()+offset);
        flipX();
        flippedX ? gun->setAnchorPoint(Vec2(0.8, 0.25)) : gun->setAnchorPoint(Vec2(0.2, 0.25));
        if(!onShot)
            flippedX ? gun->setRotation(-30.0f) : gun->setRotation(30.0f);
    }
}

void GunBase::Shot(Node* background, MapBase* map)
{
    onShot = false;
    this->background = background;
    this->map = map;
    gun->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* shot = CallFunc::create(CC_CALLBACK_0(GunBase::SetBullet, this));
    auto aim = RotateTo::create(0, 0);
    auto up = RotateTo::create(0.05, -30);
    auto down = RotateTo::create(0.05, 0);
    auto delay = RotateTo::create(1.9, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_shot = Sequence::create(onshot,aim,shot,up,down,delay,back,onshot, nullptr);
    gun->runAction(seq_shot);

}

void GunBase::SetBullet()
{

    BulletCase::create(background, GetPositionToBackground(),this->_flippedX);
    map->bullets.push_back(Bullet::create(background, GetPositionToBackground(), this->_flippedX));
    
}

void GunBase::SetShot()
{
    onShot = !onShot;
}

Vec2 GunBase::GetPositionToBackground()
{
    Vec2 hand_organ = this->getParent()->getPosition();
    Vec2 hand = this->getParent()->getParent()->getPosition();
    Vec2 player = this->getParent()->getParent()->getParent()->getPosition();

    return hand_organ + hand + player;
}
