#ifndef MAP_SPACE_H
#define MAP_SPACE_H

#include "cocos2d.h"
#include "MapBase.h"
#include "Sprite/Player1.h"
#include "Sprite/AI1.h"

USING_NS_CC;

class MapSpace : public MapBase
{
public:

	static MapBase* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

	void initPlayer();

	void ShotEvent() override;

private: 

	Vec2 initPlanet1Position;
	Vec2 initPlanet2Position;

	Sprite* planet1;
	Sprite* planet2;

	CharacterBase* player1;
	CharacterBase* player2;
};

#endif