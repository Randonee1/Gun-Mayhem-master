#include "Head.h"

bool Head::initWithName(const char* name)
{
    if (!OrganBase::initWithName(name)) {
        return false;
    }
    auto seq = Sequence::create(EaseSineOut::create(MoveBy::create(0.7, Vec2(0, -10))), 
        EaseSineOut::create(MoveBy::create(0.7, Vec2(0, 10))), nullptr);
    auto rep = RepeatForever::create(seq);
    organ->runAction(rep);
    return true;
}

Head* Head::CreateWithName(const char* name)
{
    auto head = new Head();
    if (head && head->initWithName(name)) {
        head->autorelease();
        return head;
    }
    CC_SAFE_DELETE(head);
    return NULL;
}

void Head::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        this->setPositionX(-this->getPositionX());
        flipX();
    }
}
