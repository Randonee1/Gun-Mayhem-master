#ifndef BULLET_H
#define BULLET_H

#include "cocos2d.h"

USING_NS_CC;

class CharacterBase;

class Bullet : public Sprite
{
public:

	virtual bool init(CharacterBase* player, Vec2 init, Vec2 offset);

	void update(float dt) override;

	static Bullet* create(CharacterBase* player, Vec2 init, Vec2 offset);

	float bulletSpeed;
	float hitSpeed;

	Vec2 currentPoint;

	Node* back;
	Sprite* bullet;

	CharacterBase* player;
};

#endif