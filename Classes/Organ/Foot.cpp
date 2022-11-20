#include "Foot.h"

bool Foot::initWithName(const char* name)
{
    if (!OrganBase::initWithName(name)) {
        return false;
    }
    organ->setAnchorPoint(Vec2(0.2, 0.25));
    return true;
}

Foot* Foot::CreateWithName(const char* name)
{
    auto foot = new Foot();
    if (foot && foot->initWithName(name)) {
        foot->autorelease();
        return foot;
    }
    CC_SAFE_DELETE(foot);
    return NULL;
}

void Foot::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        this->setPositionX(-this->getPositionX());
        organ->setRotation(-organ->getRotation());
        flippedX ? organ->setAnchorPoint(Vec2(0.8, 0.2)) : organ->setAnchorPoint(Vec2(0.2, 0.2));
        flipX();

        actionState = false;
        organ->stopActionByTag(10);
        //organ->setPosition(Vec2(0, 0));
    }
}

void Foot::MoveDelay(bool up, bool floor)
{
    Spawn* spa;
    int tag;
    if (!floor) {
        if (up) {
            auto moveback = MoveTo::create(0, Vec2(0, 0));
            auto move = MoveBy::create(0.1, Vec2(0, -15));
            auto seq1 = Sequence::create(moveback, move, nullptr);
            auto rotate1 = RotateTo::create(0, 80);
            //auto rotate2 = RotateTo::create(0.1, 80);
            auto seq2 = Sequence::create(rotate1,  nullptr);
            spa = Spawn::create(seq1 ,seq2, nullptr);
            tag = 1;
        }
        else {
            auto move1 = MoveTo::create(0.1, Vec2(0, 0));
            auto move2 = MoveBy::create(0.06, Vec2(0, 15));
            auto seq1  = Sequence::create(move1, move2, nullptr);
            auto rotate1 = RotateTo::create(0.06, 0);
            auto rotate2 = RotateTo::create(0.06, -20);
            auto seq2 = Sequence::create(rotate1,rotate2, nullptr);
            spa = Spawn::create(seq1, seq2, nullptr);
            tag = 2;
        }
    }
    else {
        auto moveback = MoveTo::create(0, Vec2(0, 0));
        auto seq = Sequence::create(moveback, nullptr);
        auto rotate = RotateTo::create(0, 0);
        spa = Spawn::create(seq, rotate, nullptr);
        tag = 3;
    }
    organ->stopActionByTag(lastDelayTag);
    spa->setTag(tag);
    organ->runAction(spa);
    organ->setTag(tag);

    lastDelayTag = tag;
}

void Foot::Walk(bool direction)
{
    if (!actionState) {
        Spawn* spa;
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(Foot::SetActionState, this));

        if (direction) {
            auto back = MoveTo::create(0, Vec2(0, 0));
            auto move1 = MoveBy::create(0.2f, Vec2(-20, 0));
            auto move2 = MoveBy::create(0.2f, Vec2(20, 0));
            auto rotate_back = RotateTo::create(0, 0);
            auto rotate_delay = RotateTo::create(0.2f, 0);
            auto rotate1 = RotateTo::create(0.1f, -20);
            auto rotate2 = RotateTo::create(0.1f, 0);
            auto seq1 = Sequence::create(func, back, move1, move2, func, nullptr);
            auto seq2 = Sequence::create(rotate_back, rotate_delay,rotate1, rotate2, nullptr);
            spa = Spawn::create(seq1, seq2, nullptr);
            spa->setTag(10);
        }
        if (!direction) {
            auto back = MoveTo::create(0, Vec2(0, 0));
            auto move1 = MoveBy::create(0.2f, Vec2(20, 0));
            auto move2 = MoveBy::create(0.2f, Vec2(-20, 0));
            auto rotate_back = RotateTo::create(0, 0);
            auto rotate_delay = RotateTo::create(0.2f, 0);
            auto rotate1 = RotateTo::create(0.1f, -20);
            auto rotate2 = RotateTo::create(0.1f, 0);
            auto seq1 = Sequence::create(func, back, move1, move2, func, nullptr);
            auto seq2 = Sequence::create(rotate_back, rotate1, rotate2,rotate_delay, nullptr);
            spa = Spawn::create(seq1, seq2, nullptr);
            spa->setTag(10);
        }
        organ->runAction(spa);
    }
}


void Foot::SetActionState()
{
    actionState = !actionState;
}
