#include "MapBase.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/CharacterBase.h"

bool MapBase::init()
{
	if (!Layer::init())
		return false;
	visibleSize = Director::getInstance()->getVisibleSize();

	packageEvent = PackageEvent::create(this);

	return true;
}

void MapBase::update(float dt)
{
	ShotEvent();
	packageEvent->update(dt);
	packageEvent->PackageUpdate(players);

}

void MapBase::ShotEvent()
{
	return;
}