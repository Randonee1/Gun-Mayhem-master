#ifndef GUN_BASE_H
#define GUN_BASE_H

#include "cocos2d.h"
#include "Weapons/Bullet/BulletCase.h"
#include "Weapons/Bullet/Bullet.h"
#include "Map/MapBase.h"


USING_NS_CC;

class CharacterBase;

class GunBase : public Sprite
{
public:

	virtual bool init();

	virtual GunBase* clone();
	virtual Sprite* RightGun();
	virtual Sprite* LeftGun();

	void setFlippedX(Sprite* gun, bool flippedX, bool right, float offset);

	virtual void Shot(MapBase* map, bool right);

	virtual void Change(GunBase* throwgun,bool withgun);

	virtual void Delay(bool right);

	virtual Sequence* RaiseHand(bool withgun);
	virtual Sequence* BulletChange(bool withgun);
	virtual Sequence* HoldingOn(bool withgun);

	virtual void SetBullet();

	virtual void SetBulletCase();

	void SetShot();

	void update(float dt) override;
	bool onShot = false;
	bool change = false;

	Vec2 GetPositionToBackground(bool right);
	Vec2 anchor;
	Vec2 anchor_left;

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
	bool isSniper = false;
	bool releaseToShot = false;

	Sprite* gun_left = nullptr;
	Sprite* gun_right = nullptr;
	MapBase* map;

	Sprite* gunshadow_right = nullptr;
	Sprite* gunshadow_left = nullptr;
	float gunshadow_vx;
	float gunshadow_vy;

	CharacterBase* player;
};

#endif