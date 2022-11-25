#ifndef GUN_PACKAGE_H
#define GUN_PACKAGE_H

#include "cocos2d.h"
#include "PackageBase.h"
#include "Weapons/Gun/GunBase.h"
#include "Weapons/Gun/Gun_MG_P90.h"

USING_NS_CC;

class GunPackage : public PackageBase
{
public:

	static GunPackage* createWithGun(MapBase* map);

	bool initWithGun(MapBase* map);

	void GetPackage(CharacterBase* player) override;

	void update(float dt) override;

	GunBase* gun;

};

#endif