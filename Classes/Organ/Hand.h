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

	void GoLeft();
	void GoRight();

	void MoveDelay(bool up, bool floor) override;

	void RaiseHandToShoot(Node* background);

	bool actionState = false;
	bool onShot = false;
	bool onRaise = false;

	void SetActionState();
	void SetShot();
	void SetRaise();

	GunBase* gun;
	Point gunPoint;

};

#endif