#ifndef GUN_MG_MP5_H
#define GUN_MG_MP5_H

#include "cocos2d.h"
#include "GunBase.h"
USING_NS_CC;

class Gun_MG_MP5 : public GunBase
{
public:

	static Gun_MG_MP5* create();

	Gun_MG_MP5* clone() override;
	Sprite* RightGun() override;

	bool init() override;

	void Shot(MapBase* map, bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	void SetBullet() override;

};

#endif