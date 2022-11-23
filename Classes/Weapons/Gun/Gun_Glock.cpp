#include "Gun_Glock.h"

Gun_Glock* Gun_Glock::CreateWithName(const char* name)
{
    auto gun = new Gun_Glock();
    if (gun && gun->initWithName(name)) {
        gun->autorelease();
        return gun;
    }
    CC_SAFE_DELETE(gun);
    return NULL;
}

bool Gun_Glock::initWithName(const char* name)
{
    if (!GunBase::initWithName(name))
        return false;
    anchor = Vec2(0.2, 0.25);
    initRotation = 30.0f;
    shotInterval = 0.15;
    bulletSpeed = 2000;
    bulletClip = 10;
    bulletCount = 0;

    gun->setAnchorPoint(anchor);
    gun->setRotation(initRotation);
    return true;
}

void Gun_Glock::Shot( MapBase* map)
{
    GunBase::Shot(map);
    gun->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* shot = CallFunc::create(CC_CALLBACK_0(GunBase::SetBullet, this));
    CallFunc* onfire = CallFunc::create([&]() {fire = !fire; });
    auto aim = RotateTo::create(0, 0);
    auto up = RotateTo::create(0.05, -30);
    auto down = RotateTo::create(0.05, 0);
    auto delay = RotateTo::create(1.9, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_shot = Sequence::create(onshot,onfire, aim, shot, up, down,onfire, delay, back, onshot, nullptr);
    gun->runAction(seq_shot);
}

void Gun_Glock::BulletChange()
{
    GunBase::BulletChange();
    gun->stopAllActions();
    CallFunc* onchange = CallFunc::create([&]() {onShot = !onShot; });
    CallFunc* Change = CallFunc::create([&]() {change = !change; });
    CallFunc* disappear = CallFunc::create([&]() {gun->setVisible(false); });
    CallFunc* appear = CallFunc::create([&]() {gun->setVisible(true); });

    CallFunc* gunthrow = CallFunc::create([&]() {gunshadow = Sprite::create("gun_test.png");
    gunshadow_vx = gun->isFlippedX() ? -1000 : 1000;
    gunshadow_vy = 1000;
    gunshadow->setFlippedX(gun->isFlippedX());
    gun->isFlippedX() ? gunshadow->setRotation(30) : gunshadow->setRotation(-30);
    gunshadow->setPosition(GetPositionToBackground());
    map->platform->addChild(gunshadow, 1);
    auto rotate = RepeatForever::create(RotateBy::create(0.3, gun->isFlippedX() ? 180 : -180));
    gunshadow->runAction(rotate); });

    //auto raise = RotateTo::create(0.1, -60);
    auto throwaway = RotateTo::create(0.15, -30);
    auto movedown = RotateTo::create(0.3, initRotation);
    auto moveup1 = RotateTo::create(0.1, -100);
    auto moveup2 = RotateTo::create(0.1, 130);
    auto moveup3 = RotateTo::create(0.1, 0);
    auto delay = RotateTo::create(2, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_change = Sequence::create(onchange,Change, gunthrow, disappear,throwaway,movedown,appear, moveup1,moveup2,moveup3,Change,delay,back,onchange, nullptr);
    gun->runAction(seq_change);
}

void Gun_Glock::SetBullet()
{
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 30), this->_flippedX);
    map->bullets.push_back(Bullet::create(map->platform, GetPositionToBackground(), Vec2(50, 30),bulletSpeed,this->_flippedX));
}

void Gun_Glock::update(float dt)
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
