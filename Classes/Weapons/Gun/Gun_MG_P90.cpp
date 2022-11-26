#include "Gun_MG_P90.h"


Gun_MG_P90* Gun_MG_P90::create()
{
    auto gun = new Gun_MG_P90();
    if (gun && gun->init()) {
        return gun;
    }
    CC_SAFE_DELETE(gun);
    return NULL;
}

Gun_MG_P90* Gun_MG_P90::clone()
{
    return Gun_MG_P90::create();
}

Sprite* Gun_MG_P90::ThrowGun()
{
    return Sprite::createWithSpriteFrameName("MG_P90.png");
}

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
    auto delay3 = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_shot = Sequence::create(onshot, onfire, aim,shot,delay1, onfire,delay2, delay3, back, onshot, nullptr);
    gun->runAction(seq_shot);
}


Sequence* Gun_MG_P90::RaiseHand(bool withgun)
{
    auto movebackward = EaseSineOut::create(MoveBy::create(shotInterval / 2, Vec2(-20, 0)));
    auto moveforward = EaseSineOut::create(MoveBy::create(shotInterval / 2, Vec2(20, 0)));
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(45, 30));
        return Sequence::create(raise, movebackward, moveforward,delay,down, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(40, 10));
        return Sequence::create(raise, movebackward, moveforward,delay,down, nullptr);
    }
}

void Gun_MG_P90::Delay()
{
    auto aim = RotateTo::create(0, 0);
    auto delay3 = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_delay = Sequence::create(aim, delay3, back, nullptr);
    gun->runAction(seq_delay);
}

Sequence* Gun_MG_P90::HoldingOn(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(45, 30));
        return Sequence::create(raise, delay, down, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(40, 10));
        return Sequence::create(raise, delay, down, nullptr);
    }
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

    if (gunshadow) {
        gunshadow_vy -= dt * 4000;
        Vec2 point = gunshadow->getPosition();
        point.x += gunshadow_vx * dt;
        point.y += gunshadow_vy * dt;
        gunshadow->setPosition(point);

        if (point.y < 0) {
            gunshadow->removeFromParent();
            gunshadow = nullptr;
        }
    }
}