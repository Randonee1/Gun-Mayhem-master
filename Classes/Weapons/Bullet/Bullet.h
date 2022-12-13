#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"
#

USING_NS_CC;

class Bullet : public Sprite
{
public:

	bool init(Node* back, Vec2 init, Vec2 offset,float bulletSpeed,float hitSpeed, bool direction);

	void update(float dt) override;

	static Bullet* create(Node* back, Vec2 init, Vec2 offset,float bulletSpeed,float hitSpeed, bool direction);

	float bulletSpeed;
	float hitSpeed;

	Vec2 currentPoint;

	Node* back;
	Sprite* bullet;
};

#endif