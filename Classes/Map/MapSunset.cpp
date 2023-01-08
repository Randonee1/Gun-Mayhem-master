#include "MapSunset.h"

MapSunset* MapSunset::createGame()
{
	auto layer = new MapSunset();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return NULL;
}

bool MapSunset::init()
{
	if (!MapBase::init()) {
		return false;
	}
	initBackground();

	floor_height = 260;
	floor_base = 150;
	Floor = { {688,1224},{0,289,522,1366,1599,1890},{289,1599},{522,1366}};
	death_line = -1000;

	initPlayer();

	this->scheduleUpdate();

	return true;
}

void MapSunset::update(float dt)
{
	MapBase::update(dt);

	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = Vec2(0, 0);
	for (auto &player : players) { delta += player->getPosition(); }
	delta = (delta + initPlatform * 1.5) / (players.size() + 1.5) - initPlatform;

	float a = std::pow(delta.x, 2) + std::pow(delta.y, 2);
	float b = std::pow(visibleSize.height / 1.5, 2) + std::pow(visibleSize.width / 1.5, 2);
	if (a > b) {
		delta.x = delta.x * b / a;
		delta.y = delta.y * b / a;
	}

	backLayer->setPosition(initbackLayerPosition - delta * 0.1);
	mountain1->setPosition(initMountain1Position - delta * 0.2);
	city1->setPosition(initCity1Position - delta * 0.3);
	city2->setPosition(initCity2Position - delta * 0.4);
	city3->setPosition(initCity3Position - delta * 0.5);
	mountain2->setPosition(initMountain2Position - delta * 0.6);
	platform->setPosition(initPlatformPosition - delta * 0.7);

}

void MapSunset::initBackground()
{
	backLayer = Sprite::create("sunset/background.png");
	auto backLayer_left = Sprite::create("sunset/background.png");
	auto backLayer_right = Sprite::create("sunset/background.png");
	auto sun = Sprite::create("sunset/sun.png");
	initbackLayerPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	backLayer_left->setPosition(-backLayer->getContentSize().width / 2, backLayer->getContentSize().height / 2);
	backLayer_right->setPosition(backLayer->getContentSize().width * 3 / 2, backLayer->getContentSize().height / 2);
	sun->setPosition(backLayer->getContentSize().width / 2-400, backLayer->getContentSize().height / 2 + 200);
	backLayer->addChild(backLayer_right, 0);
	backLayer->addChild(backLayer_left, 0);
	backLayer->addChild(sun, 1);
	backLayer->setPosition(initbackLayerPosition);
	this->addChild(backLayer, 0);

	mountain1 = Sprite::create("sunset/mountain.png");
	auto mountain1_left = Sprite::create("sunset/mountain.png");
	auto mountain1_right = Sprite::create("sunset/mountain.png");
	initMountain1Position = Vec2(visibleSize.width / 2, visibleSize.height / 2- 200);
	mountain1_left->setPosition(-mountain1->getContentSize().width / 2, mountain1->getContentSize().height / 2);
	mountain1_right->setPosition(mountain1->getContentSize().width * 3 / 2, mountain1->getContentSize().height / 2);
	mountain1->addChild(mountain1_left, 0);
	mountain1->addChild(mountain1_right, 0);
	mountain1->setPosition(initMountain1Position);
	this->addChild(mountain1, 1);

	city1 = Sprite::create("sunset/city1.png");
	auto city1_left = Sprite::create("sunset/city1.png");
	auto city1_right = Sprite::create("sunset/city1.png");
	initCity1Position = Vec2(visibleSize.width / 2, visibleSize.height / 2-500);
	city1_left->setPosition(-city1->getContentSize().width / 2, city1->getContentSize().height / 2);
	city1_right->setPosition(city1->getContentSize().width * 3 / 2, city1->getContentSize().height / 2);
	city1->addChild(city1_left, 0);
	city1->addChild(city1_right, 0);
	city1->setPosition(initCity1Position);
	this->addChild(city1, 2);

	city2 = Sprite::create("sunset/city2.png");
	auto city2_left = Sprite::create("sunset/city2.png");
	auto city2_right = Sprite::create("sunset/city2.png");
	initCity2Position = Vec2(visibleSize.width / 2 + 500, visibleSize.height / 2-300);
	city2_left->setPosition(-city2->getContentSize().width / 2, city2->getContentSize().height / 2);
	city2_right->setPosition(city2->getContentSize().width * 3 / 2, city2->getContentSize().height / 2);
	city2->setPosition(initCity2Position);
	city2->addChild(city2_left, 0);
	city2->addChild(city2_right, 0);
	this->addChild(city2, 3);

	city3 = Sprite::create("sunset/city3.png");
	auto city3_left = Sprite::create("sunset/city3.png");
	auto city3_right = Sprite::create("sunset/city3.png");
	initCity3Position = Vec2(visibleSize.width / 2, visibleSize.height / 2-300);
	city3_left->setPosition(-city3->getContentSize().width / 2 - 150, city3->getContentSize().height / 2 );
	city3_right->setPosition(city3->getContentSize().width * 3 / 2 + 150, city3->getContentSize().height / 2);
	city3->setPosition(initCity3Position);
	city3->addChild(city3_left, 0);
	city3->addChild(city3_right, 0);
	this->addChild(city3, 4);

	mountain2 = Sprite::create("sunset/mountain.png");
	auto mountain2_left = Sprite::create("sunset/mountain.png");
	auto mountain2_right = Sprite::create("sunset/mountain.png");
	initMountain2Position = Vec2(visibleSize.width / 2 , visibleSize.height / 2 - 700);
	mountain2_left->setPosition(-mountain2->getContentSize().width / 2 + 510, mountain2->getContentSize().height / 2);
	mountain2_right->setPosition(mountain2->getContentSize().width * 3 / 2 - 510, mountain2->getContentSize().height / 2);
	mountain2->addChild(mountain2_left, 0);
	mountain2->addChild(mountain2_right, -1);
	mountain2->setPosition(initMountain2Position);
	this->addChild(mountain2, 5);

	platform = Sprite::create("sunset/platform.png");
	initPlatformPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	platform->setPosition(initPlatformPosition);
	this->addChild(platform, 6);
	platformSize = platform->getContentSize();
}
