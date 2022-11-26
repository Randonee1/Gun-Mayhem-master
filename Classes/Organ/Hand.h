#ifndef HAND_H
#define HAND_H

#include "cocos2d.h"
#include "Weapons/Gun/GunBase.h"
#include "OrganBase.h"

USING_NS_CC;

class Hand : public OrganBase
{
public:
	static Hand* CreateWithName(const char* name);

	//void stopActionByTag(int tag);
	void GetGun(GunBase* Gun);

	void setFlippedX(bool flippedX);

	void Walk(bool direction);

	void MoveDelay(bool up, bool floor) override;

	void RaiseHandToShoot(MapBase* map,GunBase* gun,bool withgun);

	void BulletChangeWithHand(GunBase* gun,GunBase* throwgun, bool withgun);

	void DelayWithHand(GunBase* gun,bool withgun);

	bool actionState = false;
	bool onShot = false;

	void SetActionState();
	void SetShot();

	GunBase* gun;
	Point gunPoint;

};

#endif