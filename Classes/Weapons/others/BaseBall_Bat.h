#ifndef BASEBALL_BAT_H
#define BASEBALL_BAT_H

#include "cocos2d.h"
#include "Weapons/Gun/GunBase.h"
#include "Weapons/Bullet/BaseBall.h"

USING_NS_CC;

class BaseBall_Bat : public GunBase
{
public:

	static BaseBall_Bat* create();

	BaseBall_Bat* clone() override;
	Sprite* RightGun() override;
	Sprite* LeftGun() override;

	bool init() override;

	void Shot(MapBase* map, bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	void ThrowBall();

	void SetBullet() override;

	void update(float dt) override;

private:
	//bool throw_ball = false;
	bool onRaise = false;
	bool isRaise = false;
};

#endif