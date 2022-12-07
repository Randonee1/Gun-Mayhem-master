#include "Gun_Glock.h"

Gun_Glock* Gun_Glock::create()
{
    auto gun = new Gun_Glock();
    if (gun && gun->init()) {
        return gun;
    }
    CC_SAFE_DELETE(gun);
    return NULL;
}

Gun_Glock* Gun_Glock::clone()
{
    return Gun_Glock::create();
}

Sprite* Gun_Glock::ThrowGun()
{
    return Sprite::create("gun_test.png");
}

bool Gun_Glock::init()
{
    if (!GunBase::init())
        return false;

    gun = Sprite::create("gun_test.png");
    this->addChild(gun, 0);

    anchor = Vec2(0.2, 0.25);
    initRotation = 30.0f;
    shotInterval = 0.3;
    recoilSpeed = 100;
    bulletSpeed = 2000;
    hitSpeed = 700;
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
    auto delay = RotateTo::create(0.9, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_shot = Sequence::create(onshot,onfire, aim, shot, up, down,onfire, delay, back, onshot, nullptr);
    gun->runAction(seq_shot);
}

void Gun_Glock::Change(GunBase* throwgun, bool withgun)
{
    GunBase::Change(throwgun, withgun);
    gun->stopAllActions();
    CallFunc* onchange = CallFunc::create([&]() {onShot = !onShot; });
    CallFunc* Change = CallFunc::create([&]() {change = !change; });
    CallFunc* disappear = CallFunc::create([&]() {gun->setVisible(false); });
    CallFunc* appear = CallFunc::create([&]() {gun->setVisible(true); });

    CallFunc* gunthrow = CallFunc::create([&,throwgun]() {gunshadow = throwgun->ThrowGun();
    gunshadow_vx = gun->isFlippedX() ? -1000 : 1000;
    gunshadow_vy = 1000;
    gunshadow->setFlippedX(gun->isFlippedX());
    gun->isFlippedX() ? gunshadow->setRotation(30) : gunshadow->setRotation(-30);
    gunshadow->setPosition(GetPositionToBackground(1));
    map->platform->addChild(gunshadow, 1);
    auto rotate = RepeatForever::create(RotateBy::create(0.5, gun->isFlippedX() ? 180 : -180));
    gunshadow->runAction(rotate); });

    //auto raise = RotateTo::create(0.1, -60);
    auto moveback = RotateTo::create(0, 0);
    auto throwaway = RotateTo::create(0.15, -30);
    auto movedown = RotateTo::create(0.3, initRotation);
    auto moveup1 = RotateTo::create(0.1, -100);
    auto moveup2 = RotateTo::create(0.1, 130);
    auto moveup3 = RotateTo::create(0.1, 0);
    auto delay = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_change = Sequence::create(onchange,Change, gunthrow, disappear,moveback,throwaway,movedown,appear, moveup1,moveup2,moveup3,Change,delay,back,onchange, nullptr);
    gun->runAction(seq_change);
}

Sequence* Gun_Glock::RaiseHand(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        return Sequence::create(MoveTo::create(0, Vec2(70, 14)),delay,down,nullptr);
    }
    else {
        return Sequence::create(MoveTo::create(0, Vec2(15, -5)),delay,down,nullptr);
    }
}

void Gun_Glock::Delay()
{
    auto aim = RotateTo::create(0, 0);
    auto delay = RotateTo::create(0.9, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_shot = Sequence::create( aim, delay, back, nullptr);
    gun->runAction(seq_shot);
}

Sequence* Gun_Glock::HoldingOn(bool withgun)
{
    auto delay = MoveBy::create(0.9, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        return Sequence::create(MoveTo::create(0, Vec2(70, 14)), delay, down, nullptr);
    }
    else {
        return Sequence::create(MoveTo::create(0, Vec2(15, -5)), delay, down, nullptr);
    }
}

Sequence* Gun_Glock::BulletChange(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = MoveTo::create(0.3, Vec2(0, 0));
    if (withgun) {
        auto throwaway = EaseSineOut::create(MoveTo::create(0.15, Vec2(120, 64)));
        auto movedown = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
        auto moveup = EaseSineOut::create(MoveTo::create(0.3, Vec2(70, 14)));
        return Sequence::create(throwaway, movedown, moveup,delay,down, nullptr);
    }
    else {
        auto throwaway = EaseSineOut::create(MoveTo::create(0.15, Vec2(15, -5)));
        auto movedown = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
        auto moveup = EaseSineOut::create(MoveTo::create(0.3, Vec2(15, -5)));
        return Sequence::create(throwaway, movedown, moveup,delay,down, nullptr);
    }
}

void Gun_Glock::SetBullet()
{
    BulletCase::create(map->platform, GetPositionToBackground(1), Vec2(10, 30), this->_flippedX,400,800);
    map->bullets.push_back(Bullet::create(map->platform, GetPositionToBackground(1), Vec2(50, 30),bulletSpeed,hitSpeed,this->_flippedX));
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
        
        if (point.y < map->death_line) {
            gunshadow->removeFromParent();
            gunshadow = nullptr;
        }
    }
}
