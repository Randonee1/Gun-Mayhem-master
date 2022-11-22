#ifndef GUN_CLOCK_H
#define GUN_CLOCK_H

#include "cocos2d.h"
#include "GunBase.h"
USING_NS_CC;

class Gun_Glock : public GunBase
{
public:

	static Gun_Glock* CreateWithName(const char* name);

	bool initWithName(const char* name);

	void Shot(MapBase* map);

	void BulletChange();

	void SetBullet() override;

	void update(float dt) override;

};

#endif