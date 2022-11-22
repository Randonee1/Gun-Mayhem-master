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
    bulletSpeed = 2500;
    hitSpeed = 1000;
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
    CallFunc* onchange = CallFunc::create([&]() {onChange = !onChange; });
    CallFunc* Change = CallFunc::create([&]() {change = !change; });
    auto movedown = RotateTo::create(0.3, initRotation);
    auto moveup1 = RotateTo::create(0.2, -100);
    auto moveup2 = RotateTo::create(0.2, 130);
    auto moveup3 = RotateTo::create(0.2, 0);
    auto delay = RotateTo::create(1.9, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_change = Sequence::create(onchange,Change,movedown, moveup1,moveup2,moveup3,Change,delay,back,onchange, nullptr);
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


}
