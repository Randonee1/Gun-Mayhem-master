#ifndef FOOT_H
#define FOOT_H

#include "cocos2d.h"
#include "Organ/OrganBase.h"

USING_NS_CC;

class Foot : public OrganBase
{
public:
	bool initWithName(const char* name);

	static Foot* CreateWithName(const char* name);

	void setFlippedX(bool flippedX);

	void MoveDelay(bool up, bool floor)override;

	void Walk(bool direction);

	bool actionState = false;
	void SetActionState();

};

#endif