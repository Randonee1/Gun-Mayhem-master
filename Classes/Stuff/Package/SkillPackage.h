#ifndef SKILL_PACKAGE_H
#define SKILL_PACKAGE_H

#include "cocos2d.h"
#include "PackageBase.h"
#include "Skill/Defense.h"
#include "Skill/SpeedUp.h"
#include "Skill/SuperJump.h"
#include "Skill/Jetpack.h"
#include "Skill/ExtraLife.h"

USING_NS_CC;

class SkillPackage : public PackageBase
{
public:

	static float updatetime;

	static SkillPackage* createWithSkill(MapBase* map);

	bool initWithGun(MapBase* map);

	void GetPackage(CharacterBase* player) override;

	void update(float dt) override;
	 
	SkillType skill;

private:
};

#endif