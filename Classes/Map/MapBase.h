#ifndef MAP_BASE_H
#define MAP_BASE_H

#include "cocos2d.h"
#include "Layer/PlayerStateMenu.h"
#include "Weapons/Bullet/Bullet.h"
#include "Stuff/Blood.h"
#include "Manager/GameManager.h"
#include "Manager/UserManager.h"


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

	virtual void initPlayer();

	bool InTheBoundary(std::vector<float>& floor, float x) const;

	void bindPlayerStateMenu(PlayerStateMenu* playerState);

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

	PlayerStateMenu* playerState;
	
	Size visibleSize;

	Size platformSize;

	Vec2 initPlatformPosition;
	Vec2 initbackLayerPosition;

};

#endif