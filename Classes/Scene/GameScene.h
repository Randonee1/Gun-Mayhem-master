#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public Scene
{
public:
	static Scene* CreateGame(int Level);

	bool initGame(int Level);
	
};

#endif 