#ifndef BASEBALL_H
#define BASEBALL_H

#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;

class CharacterBase;

class BaseBall : public Bullet
{
public:

	bool init(CharacterBase* player, Vec2 init, Vec2 offset) override;

	void update(float dt) override;

	static BaseBall* create(CharacterBase* player, Vec2 init, Vec2 offset);

	float x_bulletSpeed;
	float y_bulletSpeed;

};

#endif