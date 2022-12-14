#ifndef GUN_DOUBLE
#define GUN_DOUBLE

#include "cocos2d.h"
#include "GunBase.h"
USING_NS_CC;

class Gun_Double : public GunBase
{
public:

	static Gun_Double* create();

	Gun_Double* clone() override;
	Sprite* RightGun() override;
	Sprite* LeftGun() override;

	bool init() override;

	void Shot(MapBase* map, bool right);

	Sequence* RaiseHand(bool withgun);

	void Delay(bool right);

	Sequence* HoldingOn(bool withgun);

	Sequence* BulletChange(bool withgun) override;

	void SetBullet_right();
	void SetBullet_left();
	
	bool gun_switch = true;

};

#endif