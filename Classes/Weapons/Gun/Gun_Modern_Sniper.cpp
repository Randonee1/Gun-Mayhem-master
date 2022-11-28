#include "Gun_Modern_Sniper.h"

Gun_Modern_Sniper* Gun_Modern_Sniper::create()
{
	auto gun = new Gun_Modern_Sniper();
	if (gun && gun->init()) {
		return gun;
	}
	CC_SAFE_DELETE(gun);
	return NULL;
}

Gun_Modern_Sniper* Gun_Modern_Sniper::clone()
{
	return Gun_Modern_Sniper::create();
}

Sprite* Gun_Modern_Sniper::ThrowGun()
{
	return Sprite::create("Sniper_Rifle.png");
}

bool Gun_Modern_Sniper::init()
{
    if (!GunBase::init())
        return false;

    gun = Sprite::create("Sniper_Rifle.png");
    this->addChild(gun, 0);

    isSniper = true;

    anchor = Vec2(0.3,0.3);
    initRotation = -70.0f;
    shotInterval = 0.55;
    recoilSpeed = 800;
    bulletSpeed = 4000;
    hitSpeed = 3000;
    bulletClip = 10;
    bulletCount = 0;

    gun->setAnchorPoint(anchor);
    gun->setRotation(initRotation);
    return true;
}

void Gun_Modern_Sniper::Shot(MapBase* map)
{
    GunBase::Shot(map);
    gun->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* shot = CallFunc::create(CC_CALLBACK_0(GunBase::SetBullet, this));
    CallFunc* bulletcase = CallFunc::create(CC_CALLBACK_0(GunBase::SetBulletCase, this));
    CallFunc* onfire = CallFunc::create([&]() {fire = !fire; });
    auto aim1 = RotateTo::create(0, 0);
    auto delay1 = RotateTo::create(0.15, 0);
    auto delay2 = RotateTo::create(0.15, 0);
    auto delay3 = RotateTo::create(0.1, 0);
    auto delay4 = RotateTo::create(0.1, 0);
    auto delay5 = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_shot = Sequence::create(onshot, onfire, aim1, shot,delay1, onfire, delay2,bulletcase, delay3,delay4,delay5, back, onshot, nullptr);
    gun->runAction(seq_shot);
}

Sequence* Gun_Modern_Sniper::RaiseHand(bool withgun)
{
    /*auto movebackward = EaseSineOut::create(MoveBy::create(0.05, Vec2(-20, 0)));
    auto moveforward = EaseSineOut::create(MoveBy::create(0.05, Vec2(20, 0)));*/

    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(45, 30));
        auto movedelay = MoveBy::create(0.5, Vec2(0, 0));
        return Sequence::create(raise,movedelay, delay, down,  nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(25, 20));

        auto move1 = EaseSineOut::create(MoveBy::create(0.15, Vec2(50, 30)));
        auto move2 = EaseSineOut::create(MoveBy::create(0.15, Vec2(-50, 0)));
        auto move3 = EaseSineOut::create(MoveBy::create(0.1, Vec2(50, 0)));
        auto move4 = EaseSineOut::create(MoveBy::create(0.1, Vec2(-50, -30)));

        return Sequence::create(raise,move1, move2, move3, move4, delay, down, nullptr);
    }
}

void Gun_Modern_Sniper::Delay()
{
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    auto aim = RotateTo::create(0, 0);
    auto delay3 = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_delay = Sequence::create(onshot,aim, delay3, back,onshot, nullptr);
    gun->runAction(seq_delay);
}

Sequence* Gun_Modern_Sniper::HoldingOn(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(45, 30));
        return Sequence::create(raise, delay, down, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(25, 20));
        return Sequence::create(raise, delay, down, nullptr);
    }
}

void Gun_Modern_Sniper::SetBullet()
{
    unsigned seed = time(0);
    map->bullets.push_back(Bullet::create(map->platform, GetPositionToBackground(), Vec2(60, 23), bulletSpeed, hitSpeed, this->_flippedX));
}

void Gun_Modern_Sniper::SetBulletCase()
{
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 20), this->_flippedX, 400, 600);
}
