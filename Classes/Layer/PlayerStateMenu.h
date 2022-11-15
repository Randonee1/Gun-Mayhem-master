#ifndef PLAYER_STATE_MENU
#define PLAYER_STATE_MENU

#include "cocos2d.h"
USING_NS_CC;

class PlayerStateMenu : public Layer
{
public:

	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(PlayerStateMenu);

	void initPlayerState();
};

#endif