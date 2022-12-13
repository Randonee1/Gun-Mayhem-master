#ifndef SAMURAI_SWORD
#define SAMURAI_SWORD

#include "cocos2d.h"
#include "Weapons/Gun/GunBase.h"

USING_NS_CC;

class Sanurai_Sword : public GunBase
{
public:

	static Sanurai_Sword* create();

	Sanurai_Sword* clone() override;
	Sprite* RightGun() override;

	bool init() override;

	void Shot(MapBase* map, bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	void update(float dt) override;

	void Jump();

	bool onSword = false;
	bool isSwing = false;
	bool chop = false;
	bool hit = false;

};

#endif