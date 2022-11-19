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
	Sprite* platform;
	Sprite* backLayer;

	float floor_height;
	float floor_base;
	std::vector<std::vector<float>> Floor;
	
protected:
	
	Size visibleSize;

	Size platformSize;

	Vec2 initPlatformPosition;
	Vec2 initbackLayerPosition;

};

#endif