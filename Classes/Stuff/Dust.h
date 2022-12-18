#ifndef DUST_H
#define DUST_H

#include "cocos2d.h"
#include "Map/MapBase.h"
USING_NS_CC;

class Dust : public Sprite
{
public:

	static void create(MapBase* map, Vec2 point);

	bool init() override;

	void update(float dt) override;

	std::vector<Sprite*> Dusts;
};

#endif