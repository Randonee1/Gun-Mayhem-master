#ifndef MAP_BASE_H
#define MAP_BASE_H

#include "cocos2d.h"
USING_NS_CC;

class MapBase : public Layer
{
public:

	bool init() override;

	CREATE_FUNC(MapBase);

	//void bindPlayerStateMenu(PlayerStateMenu* playerState);

	Sprite* background;
protected:
	Size visibleSize;

	Size backgroundSize;

	//void onEnterTransitionDidFinish() override;

	//不同关卡不同的事件处理
	//virtual void initBackground();

	//virtual void initPlatform();

	//virtual void initPlayer();
};

#endif