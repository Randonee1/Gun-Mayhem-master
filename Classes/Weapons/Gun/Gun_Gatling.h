#ifndef GUN_GATLING_H
#define GUN_GATLING_H

#include "cocos2d.h"
#include "GunBase.h"

USING_NS_CC;

class Gun_Gatling : public GunBase
{
public:

	static Gun_Gatling* create();

	Gun_Gatling* clone() override;
	Sprite* RightGun() override;

	bool init() override;

	void Shot(MapBase* map, bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	void SetBullet() override;

};

#endif