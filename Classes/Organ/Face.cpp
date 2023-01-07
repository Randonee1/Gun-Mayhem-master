#include "Face.h"

bool Face::initWithName(const char* name)
{
    if (!OrganBase::initWithName(name)) {
        return false;
    }
    auto seq = Sequence::create(EaseSineOut::create(MoveBy::create(0.7, Vec2(0, -10))),
        EaseSineOut::create(MoveBy::create(0.7, Vec2(0, 10))), nullptr);
    auto rep = RepeatForever::create(seq);
    this->runAction(rep);
    return true;
}

Face* Face::CreateWithName(const char* name)
{
    auto face = new Face();
    if (face && face->initWithName(name)) {
        face->autorelease();
        return face;
    }
    CC_SAFE_DELETE(face);
    return NULL;
}

void Face::setFlippedX(bool flippedX)
{
    organ->setFlippedX(flippedX);
    if (_flippedX != flippedX)
    {
        _flippedX = flippedX;
        //this->setPositionX(-this->getPositionX());
        Vec2 anch = organ->getAnchorPoint();
        anch.x = 1-anch.x;
        organ->setAnchorPoint(anch);
        Vec2 point = organ->getPosition();
        point.x = -point.x;
        organ->setPosition(point);
        
        flipX();
    }
}

