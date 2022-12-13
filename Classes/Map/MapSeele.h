#ifndef MAP_SEELE_H
#define MAP_SEELE_H

#include "cocos2d.h"
#include "MapBase.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/AI1.h"
#include "Sprite/Player1.h"
#include "Sprite/CharacterBase.h"

USING_NS_CC;

class MapSeele : public MapBase
{
public:

	static MapSeele* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

	void initPlayer();

	void initEyes();

	void EyeBlink();

	void ShotEvent() override;

private:

	Sprite* seele;
	Vec2 initSeelePosition;

	std::vector<Sprite*> eyes;
	std::vector<CharacterBase*> players;
	PackageEvent* packageEvent;
};

#endif