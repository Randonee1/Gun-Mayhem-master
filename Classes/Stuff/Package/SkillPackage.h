#ifndef SKILL_PACKAGE_H
#define SKILL_PACKAGE_H

#include "cocos2d.h"
USING_NS_CC;

class SkillPackage : public Sprite
{
public:

	static Scene* createScene();

	bool init() override;

	CREATE_FUNC();
};

#endif