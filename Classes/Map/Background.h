#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "cocos2d.h"
#include "MapBase.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/AI1.h"
#include "Sprite/Player1.h"
#include "Sprite/CharacterBase.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"

using namespace cocos2d;
using namespace ui;
typedef void (*pFunc)(Ref*, Widget::TouchEventType);

USING_NS_CC;

class Background : public MapBase
{
public:

	static Background* createGame();

	bool init() override;

	void update(float dt) override;

	void initBackground();

	void initPlayer();

	void ShotEvent() override;

	

private:
	Vec2 initCity1Position;
	Vec2 initCity2Position;
	Vec2 initCity3Position;
	Vec2 initMountain1Position;
	Vec2 initMountain2Position;

	Sprite* city1;
	Sprite* city2;
	Sprite* city3;
	Sprite* mountain1;
	Sprite* mountain2;

	std::vector<CharacterBase*> players;
	PackageEvent* packageEvent;

	void onMouseMove(Event* event);
	Sprite* blacksprite;
	bool move = false;

};

#endif