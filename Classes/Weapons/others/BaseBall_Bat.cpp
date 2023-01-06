#include "BaseBall_Bat.h"
#include "Sprite/CharacterBase.h"

BaseBall_Bat* BaseBall_Bat::create()
{
    auto bat = new BaseBall_Bat();
    if (bat && bat->init()) {
        return bat;
    }
    CC_SAFE_DELETE(bat);
    return NULL;
}

BaseBall_Bat* BaseBall_Bat::clone()
{
    return BaseBall_Bat::create();
}

Sprite* BaseBall_Bat::RightGun()
{
    return Sprite::create("baseball_bat.png");
}

Sprite* BaseBall_Bat::LeftGun()
{
    return Sprite::create("baseball.png");
}

bool BaseBall_Bat::init()
{
    if (!GunBase::init())
        return false;

    releaseToShot = true;

    gun_right = Sprite::create("baseball_bat.png");
    gun_left = Sprite::create("baseball.png");

    anchor = Vec2(0.3, 0.5);
    anchor_left = Vec2(0.1, 0.1);

    initRotation = 25;
    shotInterval = 0.8;
    bulletClip = 10;
    bulletCount = 0;
    bulletSpeed = 3500;
    hitSpeed = 2000;

    gun_right->setAnchorPoint(anchor);
    gun_right->setRotation(initRotation);
    gun_left->setAnchorPoint(anchor_left);
    gun_left->setRotation(initRotation);

    return true;
}

void BaseBall_Bat::Shot(MapBase* map, bool right)
{
    
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(GunBase::SetShot, this));
    if (right) {
        GunBase::Shot(map, right);
        auto onraise_begin = CallFunc::create([&]() {onRaise = true; });
        auto onraise_end = CallFunc::create([&]() {onRaise = false; isRaise = true; });
        auto raise = isRaise? RotateTo::create(0,-80) : RotateTo::create(0.2, -80);
        auto raise_delay1 = RotateTo::create(0.1, -80);
        auto throwball = CallFunc::create(CC_CALLBACK_0(BaseBall_Bat::ThrowBall, this));
        auto raise_delay2 = RotateTo::create(0.1, -80);
        auto hit1 = RotateTo::create(0.03, -170);
        auto hit_to = RotateTo::create(0, -10);
        auto hit2 = RotateTo::create(0.03, -10);
        auto bullet = CallFunc::create(CC_CALLBACK_0(BaseBall_Bat::SetBullet, this));
        auto end_delay = RotateTo::create(0.1, -10);
        auto back = RotateTo::create(0.2,initRotation);
        auto delay = RotateTo::create(0.3, initRotation);
        auto seq = Sequence::create(onshot,onraise_begin,raise,onraise_end, raise_delay1,throwball,raise_delay2,
            hit1,hit_to, hit2,bullet,end_delay, back, delay,onshot, nullptr);
        gun_right->runAction(seq);
    }
    
}

Sequence* BaseBall_Bat::RaiseHand(bool withgun)
{
    auto back = EaseSineOut::create(MoveTo::create(0.2, Vec2(0, 0)));
    auto delay = MoveBy::create(0.3, Vec2(0, 0));
    if (withgun) {
        auto raise = isRaise ? EaseSineOut::create(MoveTo::create(0, Vec2(-50, 30))) : EaseSineOut::create(MoveTo::create(0.2, Vec2(-50, 30)));
        auto raise_delay = MoveBy::create(0.2, Vec2(0, 0));
        auto hit = EaseSineOut::create(MoveBy::create(0.06, Vec2(170, 0)));
        auto end_delay = MoveBy::create(0.1, Vec2(0, 0));
        return Sequence::create(raise, raise_delay, hit,end_delay, back, delay, nullptr);
    }
    else {
        auto raise = isRaise? EaseSineOut::create(MoveTo::create(0, Vec2(35, 15))) :EaseSineOut::create(MoveTo::create(0.2, Vec2(35, 15)));
        auto up = EaseSineOut::create(MoveBy::create(0.1, Vec2(0,15)));
        auto down = EaseSineOut::create(MoveBy::create(0.1, Vec2(0, -15)));
        auto findball = MoveBy::create(0.06, Vec2(-70, -50));
        auto end_delay = MoveBy::create(0.1, Vec2(0, 0));
        return Sequence::create(raise, up, down, findball, end_delay, delay, back, nullptr);
    }
}

void BaseBall_Bat::Delay(bool right)
{
    return;
}

Sequence* BaseBall_Bat::HoldingOn(bool withgun)
{
    return Sequence::create(MoveTo::create(0, Vec2(0, 0)), nullptr);
}

void BaseBall_Bat::ThrowBall()
{
    gun_left->setVisible(false);
    //throw_ball = true;
    gunshadow_vx = isFlippedX()?-100:100;
    gunshadow_vy = 800;
    gunshadow_left = Sprite::create("baseball.png");
    Vec2 anch = anchor_left;
    isFlippedX() ? anch.x = 1 - anch.x : anch.x = anch.x;
    gunshadow_left->setAnchorPoint(anch);
    gunshadow_left->setPosition(player->hand2->getPosition() + player->hand2->organ->getPosition());
    player->addChild(gunshadow_left, 5);

}

void BaseBall_Bat::SetBullet()
{
   /* Vec2 ballpoint = gunshadow_left->getPosition() - (player->hand1->getPosition() + player->hand1->organ->getPosition());
    CCLOG("%f,%f", ballpoint.x, ballpoint.y);*/
    GunBase::SetBullet();
    isRaise = false;
    gunshadow_left->removeFromParent();
    gunshadow_left = nullptr;
    gun_left->setVisible(true);
    map->bullets.push_back(BaseBall::create(player, GetPositionToBackground(true), Vec2(0, 0)));
}

void BaseBall_Bat::update(float dt)
{
    if (onRaise) {
        shot = false;
    }
    else{
        if (deltatime < shotInterval && deltatime != 0) {
            shot = false;
        }
        else if (bulletCount > bulletClip) {
            shot = false;
        }
        else {
            shot = true;
        }
        deltatime += dt;
    }
    if (gunshadow_left) {
        Vec2 point = gunshadow_left->getPosition();
        point.x += gunshadow_vx  * dt;
        gunshadow_vy -= dt * 10000;
        point.y += gunshadow_vy  * dt;
        gunshadow_left->setPosition(point);
    }
}
