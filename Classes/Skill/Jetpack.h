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

	void Emission();

	void update(float dt) override;

private:

	Sprite* jetpack;
	std::vector<Sprite*> Exhaust;

	float anti_gravitation;
	float gravitation;

	bool onAction = true;
	bool flyable = true;
};

#endif