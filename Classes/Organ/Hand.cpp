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


void Hand::GetGun(GunBase* Gun,bool right)
{
   
    this->Gun = Gun;
    gun = right ? Gun->gun_right: Gun->gun_left;
 
    if(gun) {
        gun->setPosition(Vec2(organ->getContentSize().width / 2, organ->getContentSize().height / 2));
        right ? organ->addChild(gun, -1) : organ->addChild(gun, 1);
        gunPoint = gun->getPosition();
    }
}

void Hand::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (gun)
        Gun->setFlippedX(gun,flippedX, organ->getContentSize().width);
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

void Hand::RaiseHandToShoot(MapBase* map,bool right)
{
    onShot = false;
    organ->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(Hand::SetShot, this));
    auto raise = Gun->RaiseHand(right);
    auto seq_shot = Sequence::create(onshot, raise, onshot, nullptr);
    organ->runAction(seq_shot);
    if(this->gun)
        this->Gun->Shot(map, right);
}

void Hand::BulletChangeWithHand(GunBase* throwgun,bool right)
{
    onShot = false;
    organ->stopAllActions();
    CallFunc* onchange = CallFunc::create([&]() {onShot = !onShot; });
    auto bulletchange = throwgun->BulletChange(right);
    auto seq_change = Sequence::create(onchange,bulletchange,onchange, nullptr);
    organ->runAction(seq_change);

    this->Gun->Change(throwgun, right);
}

void Hand::DelayWithHand(bool right)
{
    onShot = false;
    organ->stopAllActions();
    CallFunc* onshot = CallFunc::create(CC_CALLBACK_0(Hand::SetShot, this));
    auto raise = Gun->HoldingOn(right);
    auto seq_shot = Sequence::create(onshot, raise, onshot, nullptr);
    organ->runAction(seq_shot);
    if (this->gun)
        this->Gun->Delay(right);
}


void Hand::SetActionState()
{
    actionState = !actionState;
}

void Hand::SetShot()
{

    onShot = !onShot;
}
