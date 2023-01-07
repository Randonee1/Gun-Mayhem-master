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

	void bindMap(MapBase* map);

	void SetLive(int live, int tag);

	void SetAmmo(int ammo, int tag);

	Sprite* CreateAvatar(int tag);

	void onEnterTransitionDidFinish() override;

	CREATE_FUNC(PlayerStateMenu);


	//void initPlayerState();
private:
	MapBase* map;

	std::map<int, Sprite*>boardPlayer;
	
	std::map<int, Sprite*>boardBack;
	
	std::map<int, Label*>livePlayer;
	
	std::map<int, Label*>ammoPlayer;
};

#endif