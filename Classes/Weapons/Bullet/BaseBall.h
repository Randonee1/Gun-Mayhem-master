#ifndef BASEBALL_H
#define BASEBALL_H

#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;

class BaseBall : public Bullet
{
public:

	bool init(Node* back, Vec2 init, Vec2 offset, float bulletSpeed, float hitSpeed, bool direction) override;

	void update(float dt) override;

	static BaseBall* create(Node* back, Vec2 init, Vec2 offset, float bulletSpeed, float hitSpeed, bool direction);

	float x_bulletSpeed;
	float y_bulletSpeed;

};

#endif