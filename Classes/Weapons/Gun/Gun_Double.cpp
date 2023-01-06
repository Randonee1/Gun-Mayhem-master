#include "Gun_Double.h"

Gun_Double* Gun_Double::create()
{
    auto gun = new Gun_Double();
    if (gun && gun->init()) {
        return gun;
    }
    CC_SAFE_DELETE(gun);
    return NULL;
}

Gun_Double* Gun_Double::clone()
{
    return Gun_Double::create();
}

Sprite* Gun_Double::RightGun()
{
    return Sprite::create("gun_test.png");
}

Sprite* Gun_Double::LeftGun()
{
    return Sprite::create("gun_test.png");
}

bool Gun_Double::init()
{
    if (!GunBase::init())
        return false;

    gun_right = Sprite::create("gun_test.png");
    gun_left = Sprite::create("gun_test.png");
    //this->addChild(gun, 0);

    anchor = Vec2(0.3, 0.25);
    anchor_left = Vec2(0.3, 0.25);
    initRotation = 30.0f;
    shotInterval = 0.2;
    recoilSpeed = 100;
    bulletSpeed = 2000;
    hitSpeed = 700;
    bulletClip = 20;
    bulletCount = 0;

    gun_right->setAnchorPoint(anchor);
    gun_left->setAnchorPoint(anchor_left);
    gun_right->setRotation(initRotation);
    gun_left->setRotation(initRotation);
    return true;
}

void Gun_Double::Shot(MapBase* map, bool right)
{
    GunBase::Shot(map, right);
    
    //CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* onshot_begin = CallFunc::create([&]() {onShot = true; });
    CallFunc* onshot_end = CallFunc::create([&]() {onShot = false; });
    CallFunc* shot_right = CallFunc::create(CC_CALLBACK_0(Gun_Double::SetBullet_right, this));//子弹射出
    CallFunc* shot_left = CallFunc::create(CC_CALLBACK_0(Gun_Double::SetBullet_left, this));
    CallFunc* onfire = CallFunc::create([&]() {fire = !fire; });//开火
    auto aim = RotateTo::create(0, 0);//瞄准 0s
    auto up = RotateTo::create(0.05, -30);// up 0.05s
    auto up_delay = RotateTo::create(0.05, 0);
    auto down = RotateTo::create(0.05, 0);// down 0.05s
    auto down_delay = RotateTo::create(0.05, 0);
    auto delay = RotateTo::create(0.9, 0);// delay 0.9s
    auto back = RotateTo::create(0.3, 30);// back 0.3s
    
    auto seq_delay = Sequence::create(onshot_begin, aim, up_delay, down_delay, delay, back, onshot_end, nullptr);
    if (right) {
        auto seq_shot = Sequence::create(onshot_begin, onfire, aim, shot_right, up, down, onfire, delay, back, onshot_end, nullptr);
        if (gun_switch)gun_right->runAction(seq_shot);
        else gun_right->runAction(seq_delay);
    }
    else {
        auto seq_shot = Sequence::create(onshot_begin, onfire, aim, shot_left, up, down, onfire, delay, back, onshot_end, nullptr);
        if (!gun_switch)gun_left->runAction(seq_shot);
        else gun_left->runAction(seq_delay);
        gun_switch = !gun_switch;
    }
}

Sequence* Gun_Double::RaiseHand(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        return Sequence::create(MoveTo::create(0, Vec2(50, 14)), delay, down, nullptr);
    }
    else {
        return Sequence::create(MoveTo::create(0, Vec2(30, 14)), delay, down, nullptr);
    }
}

void Gun_Double::Delay(bool right)
{
    onShot = true;
    CallFunc* onshot_end = CallFunc::create([&]() {onShot = false; });
    auto aim = RotateTo::create(0, 0);
    auto delay = RotateTo::create(0.9, 0);
    auto back = RotateTo::create(0.3, 30);
    auto seq_shot = Sequence::create(aim, delay, back, onshot_end, nullptr);
    if (right) {
        gun_right->setRotation(0);
        gun_right->runAction(seq_shot);
    }
    else {
        gun_left->setRotation(0);
        gun_left->runAction(seq_shot);
    }
}

Sequence* Gun_Double::HoldingOn(bool withgun)
{
    auto delay = MoveBy::create(0.9, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        return Sequence::create(MoveTo::create(0, Vec2(50, 14)), delay, down, nullptr);
    }
    else {
        return Sequence::create(MoveTo::create(0, Vec2(30, 14)), delay, down, nullptr);
    }
}

Sequence* Gun_Double::BulletChange(bool withgun)
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
        auto throwaway = EaseSineOut::create(MoveTo::create(0.15, Vec2(120, 64)));
        auto movedown = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
        auto moveup = EaseSineOut::create(MoveTo::create(0.3, Vec2(15, -5)));
        return Sequence::create(throwaway, movedown, moveup, delay, down, nullptr);
    }
}

void Gun_Double::SetBullet_right()
{
    GunBase::SetBullet();
    BulletCase::create(map->platform, GetPositionToBackground(true), Vec2(10, 30), this->_flippedX, 400, 800);
    map->bullets.push_back(Bullet::create(player, GetPositionToBackground(true), Vec2(50, 30)));
}

void Gun_Double::SetBullet_left()
{
    GunBase::SetBullet();
    BulletCase::create(map->platform, GetPositionToBackground(false), Vec2(10, 30), this->_flippedX, 400, 800);
    map->bullets.push_back(Bullet::create(player, GetPositionToBackground(false), Vec2(50, 30)));
}
