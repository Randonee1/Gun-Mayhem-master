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

	virtual bool init();

	virtual GunBase* clone();
	virtual Sprite* ThrowGun();

	void setFlippedX(bool flippedX, float offset);

	virtual void Shot(MapBase* map);

	virtual void Change(GunBase* throwgun);

	virtual void Delay();

	virtual Sequence* RaiseHand(bool withgun);
	virtual Sequence* BulletChange(bool withgun);
	virtual Sequence* HoldingOn(bool withgun);

	virtual void SetBullet();

	void SetShot();

	void update(float dt) override;
	bool onShot = false;
	bool change = false;

	Vec2 GetPositionToBackground();
	Vec2 anchor;

	float deltatime = 0;
	float shotInterval;
	float recoilSpeed;
	float initRotation;
	float bulletSpeed;
	float hitSpeed;

	int bulletClip;
	int bulletCount;

	bool shot = true;
	bool fire = false;
	bool isGatling = false;

	Sprite* gun;
	MapBase* map;

	Sprite* gunshadow = nullptr;
	float gunshadow_vx;
	float gunshadow_vy;
};

#endif