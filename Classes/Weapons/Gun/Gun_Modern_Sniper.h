#ifndef GUN_MODERN_SNIPER_H
#define GUN_MODERN_SNIPER_H

#include "cocos2d.h"
#include "GunBase.h"

USING_NS_CC;

class Gun_Modern_Sniper : public GunBase
{
public:

	static Gun_Modern_Sniper* create();

	Gun_Modern_Sniper* clone() override;
	Sprite* ThrowGun() override;

	bool init() override;

	void Shot(MapBase* map);

	Sequence* RaiseHand(bool withgun);

	void Delay();

	Sequence* HoldingOn(bool withgun);

	void SetBullet() override;

	void SetBulletCase() override;
};

#endif