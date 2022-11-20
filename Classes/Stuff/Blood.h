#ifndef BLOOD_H
#define BLOOD_H

#include "cocos2d.h"

USING_NS_CC;

class Blood : public Sprite
{
public:

	static Blood* create();

	bool init() override;

	void update(float dt) override;

	float Angle(float v_x, float v_y);

	float gravitation = -4000;

	Sprite* BloodSpurtingOut1;
	Sprite* BloodSpurtingOut2;
	Sprite* bloodDrop1;
	Sprite* bloodDrop2;
	Sprite* bloodDrop3;

	float x_speed1;
	float y_speed1;
	float x_speed2;
	float y_speed2;
	float x_speed3;
	float y_speed3;
};

#endif