#include "Gun_Gatling.h"

Gun_Gatling* Gun_Gatling::create()
{
    auto gun = new Gun_Gatling();
    if (gun && gun->init()) {
        return gun;
    }
    CC_SAFE_DELETE(gun);
    return NULL;
}

Gun_Gatling* Gun_Gatling::clone()
{
    return Gun_Gatling::create();
}

Sprite* Gun_Gatling::ThrowGun()
{
    return Sprite::createWithSpriteFrameName("Gatling.png");
}

bool Gun_Gatling::init()
{
    if (!GunBase::init())
        return false;

    isGatling = true;

    gun = Sprite::createWithSpriteFrameName("Gatling.png");
    this->addChild(gun, 0);

    anchor = Vec2(0.06, 0.7);
    initRotation = 0.0f;
    shotInterval = 0.06;
    recoilSpeed = 50;
    bulletSpeed = 2000;
    hitSpeed = 500;
    bulletClip = 200;
    bulletCount = 0;

    gun->setAnchorPoint(anchor);
    gun->setRotation(initRotation);
    return true;
}

void Gun_Gatling::Shot(MapBase* map)
{
    GunBase::Shot(map);

    gun->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* shot = CallFunc::create(CC_CALLBACK_0(GunBase::SetBullet, this));
    CallFunc* onfire = CallFunc::create([&]() {fire = !fire; });
    auto aim = RotateTo::create(0, 0);
    auto delay1 = RotateTo::create(shotInterval / 2, 0);
    auto delay2 = RotateTo::create(shotInterval / 2, 0);
    auto delay3 = RotateTo::create(0.5, 0);
    auto seq_shot = Sequence::create(onshot, onfire, aim, shot, delay1, onfire, delay2, delay3, onshot, nullptr);
    gun->runAction(seq_shot);
}


Sequence* Gun_Gatling::RaiseHand(bool withgun)
{
    auto raise = MoveTo::create(0, Vec2(0, 0));
    auto movebackward = EaseSineOut::create(MoveBy::create(shotInterval / 2, Vec2(-10, 0)));
    auto moveforward = EaseSineOut::create(MoveBy::create(shotInterval / 2, Vec2(10, 0)));
    auto delay = MoveBy::create(0.5, Vec2(0, 0));
    return Sequence::create(raise, movebackward, moveforward, delay, nullptr);
}

void Gun_Gatling::SetBullet()
{
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(50, -30), this->_flippedX, 200, 1);
    unsigned seed = time(0);
    float y = rand() % 24 + -47;
    map->bullets.push_back(Bullet::create(map->platform, GetPositionToBackground(), Vec2(200, y), bulletSpeed, hitSpeed, this->_flippedX));
}