#ifndef PACKAGE_EVENT_H
#define PACKAGE_EVENT_H

#include "cocos2d.h"
#include "GunPackage.h"

USING_NS_CC;

class PackageEvent
{
public:
	
	static PackageEvent* create(MapBase* map);

	bool init(MapBase* map);

	void PackageUpdate(std::vector<CharacterBase*>&players);

	void update(float dt);

private:

	float gunUpdateTime;

	MapBase* map;

	std::vector<PackageBase*> packages;
};

#endif