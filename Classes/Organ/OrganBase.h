#ifndef ORGAN_BASE_H
#define ORGAN_BASE_H

#include "cocos2d.h"
USING_NS_CC;

class OrganBase : public Sprite
{
public:

	bool initWithName(const char* name);

	//static OrganBase* CreateWithName(const char* name);

	virtual void setFlippedX(bool flippedX);

	virtual void MoveDelay(bool up, bool floor);

	int lastDelayTag;

	Sprite* organ;
	Sequence* seq;
};

#endif