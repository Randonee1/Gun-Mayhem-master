#ifndef GUN_MG_UZI_H
#define GUN_MG_UZI_H

#include "cocos2d.h"
#include "GunBase.h"

USING_NS_CC;

class Gun_MG_Uzi : public GunBase
{
public:

	static Gun_MG_Uzi* create();

	Gun_MG_Uzi* clone() override;
	Sprite* ThrowGun() override;

	bool init() override;

	void Shot(MapBase* map);

	Sequence* RaiseHand(bool withgun);

	void Delay();

	Sequence* HoldingOn(bool withgun);

	void SetBullet() override;
};

#endif