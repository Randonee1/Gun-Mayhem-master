#include "Gun_Revolver.h"

Gun_Revolver* Gun_Revolver::create()
{
	auto gun = new Gun_Revolver();
	if (gun && gun->init()) {
		return gun;
	}
	CC_SAFE_DELETE(gun);
	return NULL;
}

Gun_Revolver* Gun_Revolver::clone()
{
	return Gun_Revolver::create();
}

Sprite* Gun_Revolver::ThrowGun()
{
	return Sprite::create("revolver.png");
}

bool Gun_Revolver::init()
{
    if (!GunBase::init())
        return false;

    gun = Sprite::create("revolver.png");
    this->addChild(gun, 0);

    anchor = Vec2(0.25, 0.35);
    initRotation = 30.0f;
    shotInterval = 1.1;
    recoilSpeed = 500;
    bulletSpeed = 3500;
    hitSpeed = 650;
    bulletClip = 3;
    bulletCount = 0;

    gun->setAnchorPoint(anchor);
    gun->setRotation(initRotation);
    return true;
}

void Gun_Revolver::Shot(MapBase* map)
{
    GunBase::Shot(map);
    gun->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    CallFunc* shot = CallFunc::create(CC_CALLBACK_0(GunBase::SetBullet, this));
    CallFunc* bulletcase = CallFunc::create(CC_CALLBACK_0(GunBase::SetBulletCase, this));
    CallFunc* onfire = CallFunc::create([&]() {fire = !fire; });
    auto aim1 = RotateTo::create(0, 0);
    auto up = RotateTo::create(0.03, -40);
    auto down = RotateTo::create(0.03, 0);
    /*auto up2 = RotateTo::create(0.05, -10);
    auto down2 = RotateTo::create(0.05, 0);
    auto up3 = RotateTo::create(0.05, -10);
    auto down3 = RotateTo::create(0.05, 0);*/

    auto delay1 = RotateTo::create(0.2, 0);

    auto rotateup1 = RotateTo::create(0.1, -140);
    auto rotateup2 = RotateTo::create(0.1, 80);
    auto rotateup3 = RotateTo::create(0.1, -60);
    auto rotatedelay = RotateTo::create(0.15, -60);
    auto rotatedown = RotateTo::create(0.05, 0);

    auto rotateback = RotateTo::create(0.1, 0);

    auto delay2 = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_shot = Sequence::create(onshot, onfire, aim1, shot, up->clone(), down->clone(), shot, up->clone(), down->clone(), shot, up->clone(), down->clone(),
        shot, up->clone(), down->clone(), shot, up->clone(), down->clone(), onfire,delay1, rotateup1,rotateup2, rotateup3,rotatedelay,rotatedown,bulletcase,rotateback, delay2, back, onshot, nullptr);
    gun->runAction(seq_shot);
}

Sequence* Gun_Revolver::RaiseHand(bool withgun)
{
    auto movebackward = EaseSineOut::create(MoveBy::create(0.03, Vec2(-20, 0)));
    auto moveforward = EaseSineOut::create(MoveBy::create(0.03, Vec2(20, 0)));
    
    auto delay1 = MoveBy::create(0.2, Vec2(0, 0));
    auto delay2 = MoveBy::create(1, Vec2(0, 0));
    auto back = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(70, 14));
        auto up = EaseSineOut::create(MoveBy::create(0.45, Vec2(0, 70)));
        
        auto down = MoveBy::create(0.05, Vec2(0, -70));
        auto moveback = MoveTo::create(0.1, Vec2(70, 14));
        return Sequence::create(raise, movebackward->clone(), moveforward->clone(), movebackward->clone(), moveforward->clone(), movebackward->clone(), moveforward->clone(),
            movebackward->clone(), moveforward->clone(), movebackward->clone(), moveforward->clone(), delay1, up,down,moveback,delay2, back, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(5, 40));
        auto up = EaseSineOut::create(MoveTo::create(0.3, Vec2(15, -5)));
        auto updelay = MoveBy::create(0.15, Vec2(0, 15));
        auto down = MoveBy::create(0.05, Vec2(0, 0));
        auto moveback = MoveTo::create(0.1, Vec2(15,-5));
        return Sequence::create(raise, moveforward->clone(), movebackward->clone(), moveforward->clone(), movebackward->clone(), moveforward->clone(),
            movebackward->clone(), moveforward->clone(), movebackward->clone(), moveforward->clone(), delay1, up,updelay, down, moveback, delay2, back, nullptr);
    }
}

void Gun_Revolver::Delay()
{
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    auto aim = RotateTo::create(0, 0);
    auto delay = RotateTo::create(1, 0);
    auto back = RotateTo::create(0.3, initRotation);
    auto seq_delay = Sequence::create(aim, delay, back, nullptr);
    gun->runAction(seq_delay);
}

Sequence* Gun_Revolver::HoldingOn(bool withgun)
{
    auto delay = MoveBy::create(1, Vec2(0, 0));
    auto down = EaseSineOut::create(MoveTo::create(0.3, Vec2(0, 0)));
    if (withgun) {
        auto raise = MoveTo::create(0, Vec2(70, 14));
        return Sequence::create(raise, delay, down, nullptr);
    }
    else {
        auto raise = MoveTo::create(0, Vec2(15, -5));
        return Sequence::create(raise, delay, down, nullptr);
    }
}

void Gun_Revolver::SetBullet()
{
    map->bullets.push_back(Bullet::create(map->platform, GetPositionToBackground(), Vec2(50, 30), bulletSpeed, hitSpeed, this->_flippedX));
}

void Gun_Revolver::SetBulletCase()
{
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 30), this->_flippedX, 600, -500);
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 30), this->_flippedX, 400, -500);
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 30), this->_flippedX, 200, -500);
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 30), this->_flippedX, 400, -500);
    BulletCase::create(map->platform, GetPositionToBackground(), Vec2(10, 30), this->_flippedX, 600, -500);
}
