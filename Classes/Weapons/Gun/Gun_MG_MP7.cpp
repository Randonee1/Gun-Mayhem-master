#include "Gun_MG_MP7.h"

Gun_MG_MP7* Gun_MG_MP7::create()
{
    auto gun = new Gun_MG_MP7();
    if (gun && gun->init()) {
        return gun;
    }
    CC_SAFE_DELETE(gun);
    return NULL;
}

Gun_MG_MP7* Gun_MG_MP7::clone()
{
    return Gun_MG_MP7::create();
}

Sprite* Gun_MG_MP7::ThrowGun()
{
    return Sprite::createWithSpriteFrameName("MG_MP7.png");
}

bool Gun_MG_MP7::init()
{
    if (!GunBase::init())
        return false;

    gun = Sprite::createWithSpriteFrameName("MG_MP7.png");
    this->addChild(gun, 0);

    anchor = Vec2(0.52, 0.5);
    initRotation = 20.0f;
    shotInterval = 0.08;
    recoilSpeed = 100;
    bulletSpeed = 2000;
    hitSpeed = 450;
    bulletClip = 30;
    bulletCount = 0;

    gun->setAnchorPoint(anchor);
    gun->setRotation(initRotation);
    return true;
}

void Gun_MG_MP7::Shot(MapBase* map)
{
    GunBase::Shot(map);
    gun->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* shot = CallFunc::create(CC_CALLBACK_0(GunBase::SetBullet, this));
    CallFunc* onfire = CallFunc::create([&]() {fire = !fire; });
    auto aim1 = RotateTo::create(0, -3);
    auto up = RotateTo::create(shotInterval / 3, -5);
    auto down = RotateTo::create(shotInterval / 3, -3);
    auto aim2 = RotateTo::create(0.1, 0);
    auto delay3 = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_shot = Sequence::create(onshot, onfire, aim1, shot, up, onfire, down, aim2, delay3, back, onshot, nullptr);
    gun->runAction(seq_shot);
}

Sequence* Gun_MG_MP7::RaiseHand(bool withgun)
{
    auto movebackward = EaseSineOut::create(MoveBy::create(shotInterval / 3, Vec2(-5, 0)));
    auto moveforward = EaseSineOut::create(MoveBy::create(shotInterval / 3, Vec2(5, 0)));
    auto delay1 = MoveBy::create(0.1, Vec2(0, 0));
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(45, 30));
        return Sequence::create(raise, movebackward, moveforward, delay1, delay, down, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(25, 25));
        return Sequence::create(raise, movebackward, moveforward, delay1, delay, down, nullptr);
    }
}

void Gun_MG_MP7::Delay()
{
    auto aim = RotateTo::create(0, 0);
    auto delay3 = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_delay = Sequence::create(aim, delay3, back, nullptr);
    gun->runAction(seq_delay);
}

Sequence* Gun_MG_MP7::HoldingOn(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(45, 30));
        return Sequence::create(raise, delay, down, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(25, 25));
        return Sequence::create(raise, delay, down, nullptr);
    }
}

void Gun_MG_MP7::SetBullet()
{
    BulletCase::create(map->platform, GetPositionToBackground(1), Vec2(10, 20), this->_flippedX, 400, 400);
    unsigned seed = time(0);
    float y = rand() % 16 + 15;
    map->bullets.push_back(Bullet::create(map->platform, GetPositionToBackground(1), Vec2(60, y), bulletSpeed, hitSpeed, this->_flippedX));
}
