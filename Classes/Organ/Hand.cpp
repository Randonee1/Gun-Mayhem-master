#include "Hand.h"


Hand* Hand::CreateWithName(const char* name)
{
    auto hand = new Hand();
    if (hand && hand->initWithName(name)) {
        hand->autorelease();
        return hand;
    }
    CC_SAFE_DELETE(hand);
    return NULL;
}


void Hand::GetGun(GunBase* Gun)
{
    if(Gun) {
        gun = Gun;
        gun->setPosition(Vec2(organ->getContentSize().width / 2, organ->getContentSize().height / 2));
        organ->addChild(gun, -1);
        gunPoint = gun->getPosition();
    }
    else if(gun) {
        gun->removeFromParent();
        gun = nullptr;
    }
}

void Hand::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (gun)
        gun->setFlippedX(flippedX, organ->getContentSize().width);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        //organ->setPositionX(-organ->getPositionX());
        this->setPositionX(-this->getPositionX());
        flipX();

        actionState = false;
        organ->stopActionByTag(10);
        if(! onShot)
            organ->setPosition(Vec2(0, 0));
    }
}

void Hand::Walk(bool direction)
{
    if (!actionState && !onShot) {

        Sequence* seq;
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(Hand::SetActionState, this));

        if (direction) {
            seq = Sequence::create(func, MoveTo::create(0, Vec2(0, 0)), MoveBy::create(0.2f, Vec2(-10, 0)), MoveBy::create(0.2f, Vec2(10, 0)), func, nullptr);
            seq->setTag(10);
        }
        if (!direction) {
            seq = Sequence::create(func, MoveTo::create(0, Vec2(0, 0)), MoveBy::create(0.2f, Vec2(10, 0)), MoveBy::create(0.2f, Vec2(-10, 0)), func, nullptr);
            seq->setTag(10);
        }
        organ->runAction(seq);
    }
}


void Hand::MoveDelay(bool up, bool floor)
{
    if (!onShot)
        OrganBase::MoveDelay(up, floor);
}

void Hand::RaiseHandToShoot(MapBase* map,GunBase* gun,bool withgun)
{
    onShot = false;
    organ->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(Hand::SetShot, this));
    auto raise = gun->RaiseHand(withgun);
    auto seq_shot = Sequence::create(onshot, raise, onshot, nullptr);
    organ->runAction(seq_shot);
    if(this->gun)
        this->gun->Shot(map);
}

void Hand::BulletChangeWithHand(GunBase* gun, GunBase* throwgun,bool withgun)
{
    onShot = false;
    organ->stopAllActions();
    CallFunc* onchange = CallFunc::create([&]() {onShot = !onShot; });
    auto bulletchange = gun->BulletChange(withgun);
    auto seq_change = Sequence::create(onchange,bulletchange,onchange, nullptr);
    organ->runAction(seq_change);

    if (this->gun)
        this->gun->Change(throwgun, withgun);
}

void Hand::DelayWithHand(GunBase* gun,bool withgun)
{
    onShot = false;
    organ->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(Hand::SetShot, this));
    auto raise = gun->HoldingOn(withgun);
    auto seq_shot = Sequence::create(onshot, raise, onshot, nullptr);
    organ->runAction(seq_shot);
    if (withgun)
        gun->Delay();
}

void Hand::SetActionState()
{
    actionState = !actionState;
}

void Hand::SetShot()
{

    onShot = !onShot;
}
