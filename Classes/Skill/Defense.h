#ifndef DEFENSE_H
#define DEFENSE_H

#include "cocos2d.h"
#include "SkillBase.h"
USING_NS_CC;

class Defense : public SkillBase
{
public:
	Defense(CharacterBase* player,float time = 5);
	~Defense();
private:
	Sprite* cover;
};

#endif