#ifndef GUN_BASE_H
#define GUN_BASE_H

#include "cocos2d.h"
#include "Weapons/Bullet/BulletCase.h"
#include "Weapons/Bullet/Bullet.h"
#include "Map/MapBase.h"


USING_NS_CC;

class GunBase : public Sprite
{
public:

	virtual bool initWithName(const char* name);

	//static GunBase* CreateWithName(const char* name);

	void setFlippedX(bool flippedX, float offset);

	virtual void Shot(MapBase* map);

	virtual void BulletChange();

	virtual MoveTo* RaiseHand(bool withgun);

	virtual void SetBullet();

	void SetShot();

	void update(float dt) override;
	bool onShot = false;

	Vec2 GetPositionToBackground();
	Vec2 anchor;

	float deltatime = 0;
	float shotInterval;
	float initRotation;
	float bulletSpeed;

	int bulletClip;
	int bulletCount;
	bool shot = true;
	Sprite* gun;
	MapBase* map;
};

#endif