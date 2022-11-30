#ifndef SKILL_BASE_H
#define SKILL_BASE_H

#include "cocos2d.h"
#include "Sprite/CharacterBase.h"
USING_NS_CC;

class SkillBase
{
public:
	SkillBase();
	virtual ~SkillBase();

	virtual void update(float dt);

	CharacterBase* player;

	float Duration;
	float duration;
};

#endif