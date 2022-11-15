#include "Body.h"

bool Body::initWithName(const char* name)
{
    if (!OrganBase::initWithName(name)) {
        return false;
    }
    this->setTag(0);
    organ->setTag(0);
    return true;
}

Body* Body::CreateWithName(const char* name)
{
    auto body = new Body();
    if (body && body->initWithName(name)) {
        body->autorelease();
        return body;
    }
    CC_SAFE_DELETE(body);
    return NULL;
}

//void Body::setFlippedX(bool flippedX)
//{
//    body->setFlippedX(flippedX);
//    if (_flippedX != flippedX)
//    {
//        _flippedX = flippedX;
//        this->setPositionX(-this->getPositionX());
//        flipX();
//    }
//}
