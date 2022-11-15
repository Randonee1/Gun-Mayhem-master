#ifndef GUN_BASE_H
#define GUN_BASE_H

#include "cocos2d.h"
#include "Weapons/Bullet/BulletCase.h"
#include "Weapons/Bullet/Bullet.h"
USING_NS_CC;

class GunBase : public Sprite
{
public:

	bool initWithName(const char* name);

	static GunBase* CreateWithName(const char* name);

	void setFlippedX(bool flippedX, float offset);

	void Shot(Node* background);

	void SetBullet();

	void SetShot();
	bool onShot = false;

	Vec2 GetPositionToBackground();

	Sprite* gun;
	Node* background;
};

#endif