#include "Gun_MG_P90.h"


bool Gun_MG_P90::init()
{
    if (!GunBase::init())
        return false;

    gun = Sprite::createWithSpriteFrameName("MG_P90.png");
    this->addChild(gun, 0);

    anchor = Vec2(0.35, 0.5);
    initRotation = 20.0f;
    shotInterval = 0.08;
    recoilSpeed = 100;
    bulletSpeed = 2000;
    hitSpeed = 500;
    bulletClip = 50;
    bulletCount = 0;

    gun->setAnchorPoint(anchor);
    gun->setRotation(initRotation);
    return true;
}

void Gun_MG_P90::Shot(MapBase* map)
{
    GunBase::Shot(map);
    gun->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* shot = CallFunc::create(CC_CALLBACK_0(GunBase::SetBullet, this));
    CallFunc* onfire = CallFunc::create([&]() {fire = !fire; });
    auto aim = RotateTo::create(0, 0);
    auto delay1 = RotateTo::create(shotInterval / 2, 0);
    auto delay2 = RotateTo::create(shotInterval / 2, 0);
    auto delay3 = RotateTo::create(2, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_shot = Sequence::create(onshot, onfire, aim,shot,delay1, onfire,delay2, delay3, back, onshot, nullptr);
    gun->runAction(seq_shot);
}

void Gun_MG_P90::BulletChange()
{
    GunBase::BulletChange();
    gun->stopAllActions();
}

Sequence* Gun_MG_P90::RaiseHand(bool withgun)
{
    auto movebackward = EaseSineOut::create(MoveBy::create(shotInterval / 2, Vec2(-20, 0)));
    auto moveforward = EaseSineOut::create(MoveBy::create(shotInterval / 2, Vec2(20, 0)));

    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(45, 30));
        return Sequence::create(raise, movebackward, moveforward, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(40, 10));
        return Sequence::create(raise, movebackward, moveforward, nullptr);
    }
}

Sequence* Gun_MG_P90::BulletChange(bool withgun)
{
    return nullptr;
}

void Gun_MG_P90::SetBullet()
{
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 20), this->_flippedX,300,1);
    unsigned seed = time(0);
    float y = rand() % 16 + 10;
    map->bullets.push_back(Bullet::create(map->platform, GetPositionToBackground(), Vec2(60, y), bulletSpeed, hitSpeed, this->_flippedX));
}

void Gun_MG_P90::update(float dt)
{
    GunBase::update(dt);
}
