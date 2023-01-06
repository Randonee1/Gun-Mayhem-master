#ifndef PLAYER_STATE_MENU
#define PLAYER_STATE_MENU

#include "cocos2d.h"
USING_NS_CC;

class MapBase;

class PlayerStateMenu : public Layer
{
public:

	//static Scene* createScene();

	bool init() override;

	void SetLive(const char*);

	void bindMap(MapBase* map);

	Sprite* CreateAvatar(int tag);

	void onEnterTransitionDidFinish() override;

	CREATE_FUNC(PlayerStateMenu);


	//void initPlayerState();
private:
	MapBase* map;

	Sprite* boardPlayer1;
	Sprite* boardPlayer2;
	Sprite* boardBack1;
	Sprite* boardBack2;
	Label* livePlayer1;
	Label* livePlayer2;
};

#endif