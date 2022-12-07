#ifndef JETPACK_H
#define JETPACK_H

#include "cocos2d.h"
#include "SkillBase.h"

USING_NS_CC;

class Jetpack : public SkillBase
{
public: 
	Jetpack(CharacterBase* player);

	~Jetpack();

	void update(float dt) override;

private:

	float anti_gravitation;
	float gravitation;
	bool onAction = true;
	
};

#endif