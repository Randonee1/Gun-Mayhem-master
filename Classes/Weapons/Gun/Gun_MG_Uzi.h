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
	Sprite* RightGun() override;

	bool init() override;

	void Shot(MapBase* map, bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	void SetBullet() override;
};

#endif