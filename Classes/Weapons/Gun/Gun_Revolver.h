#ifndef GUN_REVOLVER_H
#define GUN_REVOLVER_H

#include "cocos2d.h"
#include "GunBase.h"

USING_NS_CC;

class Gun_Revolver : public GunBase
{
public:

	static Gun_Revolver* create();

	Gun_Revolver* clone() override;
	Sprite* RightGun() override;

	bool init() override;

	void Shot(MapBase* map, bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	void SetBullet() override;

	void SetBulletCase() override;
};

#endif