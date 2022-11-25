#ifndef GUN_MG_P90_H
#define GUN_MG_P90_H

#include "cocos2d.h"
#include "GunBase.h"
USING_NS_CC;

class Gun_MG_P90 : public GunBase
{
public:

	//CREATE_FUNC(Gun_MG_P90);

	static Gun_MG_P90* create();

	Gun_MG_P90* clone() override;
	Sprite* ThrowGun() override;

	bool init() override;

	void Shot(MapBase* map);

	void Change(GunBase* throwgun);

	Sequence* RaiseHand(bool withgun);

	Sequence* BulletChange(bool withgun);

	void SetBullet() override;

	void update(float dt) override;

	//Sprite* gunshadow = nullptr;
	/*float gunshadow_vx;
	float gunshadow_vy;*/
};

#endif