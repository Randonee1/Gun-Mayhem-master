#ifndef SPEED_UP_H
#define SPEED_UP_H

#include "cocos2d.h"
#include "SkillBase.h"

USING_NS_CC;

struct Shadow {
	Sprite* figure;
	Vec2 point;
	Shadow* next;
	Shadow* last;
	
	Shadow(Sprite* figure,Vec2 point, Shadow* last) {
		this->figure = figure;
		this->point = point;
		this->last = last;
		this->next = nullptr;
	}
};

class SpeedUp : public SkillBase
{
public:
	SpeedUp(CharacterBase* player);

	~SpeedUp();

	Sprite* Figure(Shadow* shadow, float ocpacity);

	void update(float dt) override;

private:
	float acceleration;
	float x_maxSpeed;

	float shadow_interval = 0.03;
	float shadow_deltatime = 0;

	int shadow_size = 6;
	int shadow_number = 0;
	
	Shadow* head = nullptr;
	Shadow* tail = nullptr;
};

#endif