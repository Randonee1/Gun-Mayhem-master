#ifndef GUN_CLOCK_H
#define GUN_CLOCK_H

#include "cocos2d.h"
#include "GunBase.h"
USING_NS_CC;

class Gun_Glock : public GunBase
{
public:

	//CREATE_FUNC(Gun_Glock);

	static Gun_Glock* create();

	Gun_Glock* clone() override;
	Sprite* RightGun() override;

	bool init()override;

	void Shot(MapBase* map, bool right);

	void Change(GunBase* throwgun,bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	//Sequence* BulletChange(bool withgun);

	void SetBullet() override;

	void GunThrow(GunBase* throwgun, bool flipped, bool right);

	void update(float dt) override;

};

#endif