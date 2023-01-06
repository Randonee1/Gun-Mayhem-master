#include "Hat.h"

bool Hat::initWithName(const char* name)
{
    if (!Sprite::init()) {
        return false;
    }
    this->name = name;
    if (name != nullptr) organ = Sprite::createWithSpriteFrameName(name);
    else organ = new Sprite();
    this->addChild(organ, 0);
    auto seq = Sequence::create(EaseSineOut::create(MoveBy::create(0.7, Vec2(0, -10))),
        EaseSineOut::create(MoveBy::create(0.7, Vec2(0, 10))), nullptr);
    auto rep = RepeatForever::create(seq);
    this->runAction(rep);
    return true;
}

Hat* Hat::CreateWithName(const char* name)
{
    auto hat = new Hat();
    if (hat && hat->initWithName(name)) {
        hat->autorelease();
        return hat;
    }
    CC_SAFE_DELETE(hat);
    return NULL;
}

void Hat::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        /*Vec2 anch = organ->getAnchorPoint();
        anch.x = 1 - anch.x;
        organ->setAnchorPoint(anch);*/
        Vec2 point = organ->getPosition();
        point.x = -point.x;
        organ->setPosition(point);
        _flippedX = flippedX;
        //this->setPositionX(-this->getPositionX());
        flipX();
    }
}
