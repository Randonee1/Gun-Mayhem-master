#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

class AnimationManager
{
public:

	static AnimationManager* getInstance();

private:
	static AnimationManager* _instance;
};

#endif