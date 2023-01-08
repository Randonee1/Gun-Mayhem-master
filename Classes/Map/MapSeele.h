#ifndef MAP_SEELE_H
#define MAP_SEELE_H

#include "cocos2d.h"
#include "MapBase.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/AI2.h"
#include "Sprite/Player2.h"
#include "Sprite/CharacterBase.h"

USING_NS_CC;

class MapSeele : public MapBase
{
public:

	static MapSeele* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

	void initEyes();

	void EyeBlink();

private:

	Sprite* seele;
	Vec2 initSeelePosition;
	std::vector<Sprite*> eyes;
	
};

#endif