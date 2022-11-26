#ifndef GUN_MG_MP7_H
#define GUN_MG_MP7_H

#include "cocos2d.h"
#include "GunBase.h"
USING_NS_CC;

class Gun_MG_MP7 : public GunBase
{
public:

	static Gun_MG_MP7* create();

	Gun_MG_MP7* clone() override;
	Sprite* ThrowGun() override;

	bool init() override;

	void Shot(MapBase* map);

	Sequence* RaiseHand(bool withgun);

	void Delay();

	Sequence* HoldingOn(bool withgun);

	void SetBullet() override;
};

#endif