#include "MapTest.h"


MapTest* MapTest::createGame()
{
	auto layer = new MapTest();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return NULL;
}

bool MapTest::init()
{
	if (!MapBase::init()) {
		return false;
	}
	initBackground();

	floor_height = 270;
	floor_base = platform->getContentSize().height + 30 - 270;
	Floor = { {0, 1945}, {270, 1675} };
	death_line = 0;

	initPlayer();

	this->scheduleUpdate();

	return true;
}

void MapTest::update(float dt)
{
	MapBase::update(dt);
	
	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = Vec2(0, 0);
	for (auto& player : players) { delta += player->getPosition();}
	delta = (delta  + initPlatform*3.5) / (players.size() + 3.5) - initPlatform;

	float a = std::pow(delta.x, 2) + std::pow(delta.y, 2);
	float b = std::pow(visibleSize.height/2 , 2) + std::pow(visibleSize.width/2 , 2);
	if (delta.y < 0 && a > b) {
		delta.x = delta.x * std::sqrt(b) / std::sqrt(a);
		delta.y = delta.y * std::sqrt(b) / std::sqrt(a);
	}

	background->setPosition(initBackgroundPosition - delta * 0.5);
	backLayer->setPosition(initbackLayerPosition - delta*0.5);
	platform->setPosition(initPlatformPosition - delta*0.7);
	
}

void MapTest::initBackground()
{
	background = Sprite::create("grey_background.png");
	initBackgroundPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	background->setPosition(initBackgroundPosition);
	this->addChild(background, 0);

	backLayer = Sprite::createWithSpriteFrameName("bgd_weapontest_0.png");
	initbackLayerPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	backLayer->setPosition(initbackLayerPosition);
	this->addChild(backLayer, 0);

	platform = Sprite::createWithSpriteFrameName("bgd_weapontest_1.png");
	initPlatformPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200);
	platform->setPosition(initPlatformPosition);
	this->addChild(platform, 1);

	platformSize = platform->getContentSize();

}