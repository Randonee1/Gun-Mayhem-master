#ifndef MAP_SUNSET_H
#define MAP_SUNSET_H

#include "cocos2d.h"
#include "MapBase.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/AI2.h"
#include "Sprite/Player2.h"
#include "Sprite/CharacterBase.h"


USING_NS_CC;

class MapSunset : public MapBase
{
public:

	static MapSunset* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

private:
	Vec2 initCity1Position;
	Vec2 initCity2Position;
	Vec2 initCity3Position;
	Vec2 initMountain1Position;
	Vec2 initMountain2Position;

	Sprite* city1;
	Sprite* city2;
	Sprite* city3;
	Sprite* mountain1;
	Sprite* mountain2;

};

#endif