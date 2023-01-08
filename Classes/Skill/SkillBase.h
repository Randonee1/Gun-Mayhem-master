#ifndef SKILL_BASE_H
#define SKILL_BASE_H

#include "cocos2d.h"
#include "Sprite/CharacterBase.h"
USING_NS_CC;

enum SkillType { DEFENSE, JETPACK, SPEED_UP, SUPER_JUMP, DOUBLE_TEAM, EXTRA_LIFE ,NONE};

class SkillBase
{
public:
	SkillBase();
	virtual ~SkillBase();

	virtual void update(float dt);

	CharacterBase* player;

	SkillType skillTpye;

	bool skillEnd = false;

	float Duration;
	float duration;

};

#endif