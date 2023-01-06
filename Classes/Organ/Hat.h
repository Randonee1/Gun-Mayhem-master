#ifndef HAT_H
#define HAT_H

#include "cocos2d.h"
#include "Organ/OrganBase.h"
USING_NS_CC;

class Hat : public OrganBase
{
public:

	bool initWithName(const char* name);

	static Hat* CreateWithName(const char* name);

	void setFlippedX(bool flippedX);
};

#endif