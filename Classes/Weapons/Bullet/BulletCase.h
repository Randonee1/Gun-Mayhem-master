#ifndef BULLET_CASE_H
#define BULLET_CASE_H

#include "cocos2d.h"
#include "cstdlib"
#include "ctime"
USING_NS_CC;

class BulletCase : public Sprite
{
public:

	bool init(Node* back, Vec2 init,Vec2 offset,bool direction);

	void update(float dt) override;

	static BulletCase* create(Node* back, Vec2 init,Vec2 offset, bool direction);

	float x_speed;
	float y_speed;
	float gravitation = -4000;
	Vec2 currentPoint;

	Sprite* bulletcase;

};

#endif