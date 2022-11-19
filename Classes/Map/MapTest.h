#ifndef MAP_TEST_H
#define MAP_TEST_H

#include "cocos2d.h"
#include "Map/MapBase.h"
#include "Sprite/PlayerBase.h"
#include "Sprite/Player_test.h"
#include "Sprite/Player1.h"

USING_NS_CC;

class MapTest : public MapBase
{
public:

	static MapTest* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

	void initPlayer();


private:

	PlayerBase* player1;
	PlayerBase* player2;

	float delaytime = 0;
	
};

#endif