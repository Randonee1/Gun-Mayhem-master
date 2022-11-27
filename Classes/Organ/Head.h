#ifndef HEAD_H
#define HEAD_H

#include "cocos2d.h"
#include "OrganBase.h"

USING_NS_CC;

class Head : public OrganBase
{
public:

	bool initWithName(const char* name) ;

	static Head* CreateWithName(const char* name);

	void setFlippedX(bool flippedX);
};

#endif