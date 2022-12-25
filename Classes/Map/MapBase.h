#ifndef MAP_BASE_H
#define MAP_BASE_H

#include "cocos2d.h"
#include "Weapons/Bullet/Bullet.h"
#include "Stuff/Blood.h"

USING_NS_CC;

class PackageEvent;

class CharacterBase;

class MapBase : public Layer
{
public:

	bool init() override;

	CREATE_FUNC(MapBase);

	void update(float dt) override;

	virtual void ShotEvent();

	//void bindPlayerStateMenu(PlayerStateMenu* playerState);
	Sprite* platform;
	Sprite* backLayer;

	float floor_height;
	float floor_base;
	float death_line;
	std::vector<std::vector<float>> Floor;
	std::vector<Bullet*>bullets;
	std::vector<CharacterBase*> players;
	PackageEvent* packageEvent;
protected:
	
	Size visibleSize;

	Size platformSize;

	/*PackageEvent* packageEvent;*/

	Vec2 initPlatformPosition;
	Vec2 initbackLayerPosition;

};

#endif