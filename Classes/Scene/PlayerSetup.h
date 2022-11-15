#ifndef PLAYER_SETUP_H
#define PLAYER_SETUP_H

#include "cocos2d.h"
USING_NS_CC;

class PlayerSetup : public Layer
{
public:

	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(PlayerSetup);
};

#endif