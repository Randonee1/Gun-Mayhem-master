#ifndef DOUBLE_TEAM_H
#define DOUBLE_TEAM_H

#include "cocos2d.h"
#include "SkillBase.h"

USING_NS_CC;

class DoubleTeam : public SkillBase
{
public:
	DoubleTeam(CharacterBase* player);
	~DoubleTeam();

	void update(float dt) override;

private:

};

#endif