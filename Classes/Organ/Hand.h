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
	void GetGun(GunBase* Gun,bool right);

	void setFlippedX(bool flippedX);

	void Walk(bool direction);

	void MoveDelay(bool up, bool floor) override;

	void RaiseHandToShoot(MapBase* map,bool right);

	void BulletChangeWithHand(GunBase* throwgun, bool right);

	void DelayWithHand(bool right);

	bool actionState = false;
	bool onShot = false;

	void SetActionState();
	void SetShot();

	GunBase* Gun;
	Sprite* gun = nullptr;
	Point gunPoint;
	bool isRight;

};

#endif