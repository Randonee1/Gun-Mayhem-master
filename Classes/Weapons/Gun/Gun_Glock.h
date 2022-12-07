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
	Sprite* ThrowGun() override;

	bool init()override;

	void Shot(MapBase* map);

	void Change(GunBase* throwgun,bool withgun);

	Sequence* RaiseHand(bool withgun);

	void Delay();

	Sequence* HoldingOn(bool withgun);

	Sequence* BulletChange(bool withgun);

	void SetBullet() override;

	void update(float dt) override;

};

#endif