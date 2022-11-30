#include "OrganBase.h"

bool OrganBase::initWithName(const char* name)
{
    if (!Sprite::init()) {
        return false;
    }
    //organ = Sprite::create(name);
    this->name = name;
    organ = Sprite::createWithSpriteFrameName(name);
    this->addChild(organ, 0);
    return true;
}


void OrganBase::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        this->setPositionX(-this->getPositionX());
        flipX();
    }
}

void OrganBase::MoveDelay(bool up, bool floor)
{
    Sequence* seq;
    int tag;
    if (!floor) {
        if (up) {
            auto moveback = MoveTo::create(0, Vec2(0, 0));
            auto move = MoveBy::create(0.1, Vec2(0, -15));
            seq = Sequence::create(moveback, move, nullptr);
            tag = 1;
        }
        else {
            auto move1 = MoveTo::create(0.1, Vec2(0, 0));
            auto move2 = MoveBy::create(0.06, Vec2(0, 15));
            seq = Sequence::create(move1, move2, nullptr);
            tag = 2;
        }
    }
    else {
        auto moveback = MoveTo::create(0.00, Vec2(0, 0));
        seq = Sequence::create(moveback, nullptr);
        tag = 3;
    }
    organ->stopActionByTag(lastDelayTag);
    seq->setTag(tag);
    organ->runAction(seq);
    organ->setTag(tag);

    lastDelayTag = tag;
}
