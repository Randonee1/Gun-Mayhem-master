#ifndef BODY_H
#define BODY_H

#include "cocos2d.h"
#include "Organ/OrganBase.h"

USING_NS_CC;

class Body : public OrganBase
{
public:

	bool Body::initWithName(const char* name);

	static Body* CreateWithName(const char* name);

};

#endif