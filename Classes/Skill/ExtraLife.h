#ifndef EXTRA_LIFE_H
#define EXTRA_LIFE_H

#include "cocos2d.h"
#include "SkillBase.h"
USING_NS_CC;

class ExtraLife : public SkillBase
{
public:
	ExtraLife(CharacterBase* player);
	~ExtraLife();
};

#endif