#ifndef FACE_H
#define FACE_H

#include "cocos2d.h"
#include "Organ/OrganBase.h"

USING_NS_CC;

class Face : public OrganBase
{
public:

	bool initWithName(const char* name);

	static Face* CreateWithName(const char* name);

	void setFlippedX(bool flippedX);

};

#endif