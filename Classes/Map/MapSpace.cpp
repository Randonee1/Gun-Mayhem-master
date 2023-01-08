#include "MapSpace.h"

MapSpace* MapSpace::createGame()
{
	auto layer = new MapSpace();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return NULL;
}

bool MapSpace::init()
{
	if (!MapBase::init()) {
		return false;
	}
	initBackground();

	floor_height = 260;
	floor_base = 200;
	Floor = { {50,976,1216, 2143},{373,811,1394,1832},{877,1315},{373,811,1394,1832}, {50,976,1216, 2143}};
	death_line = -1000;

	initPlayer();

	this->scheduleUpdate();

	return true;
}

void MapSpace::update(float dt)
{
	MapBase::update(dt);

	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = Vec2(0, 0);
	for (auto& player : players) { delta += player->getPosition(); }
	delta = (delta + initPlatform * 1) / (players.size() + 1) - initPlatform;

	float a = std::pow(delta.x, 2) + std::pow(delta.y, 2);
	float b = std::pow(visibleSize.height / 1.5, 2) + std::pow(visibleSize.width / 1.5, 2);
	if (a > b) {
		delta.x = delta.x * b / a;
		delta.y = delta.y * b / a;
	}

	planet1->setPosition(initPlanet1Position - delta * 0.3);
	planet2->setPosition(initPlanet2Position - delta * 0.2);
	backLayer->setPosition(initbackLayerPosition - delta * 0.5);
	platform->setPosition(initPlatformPosition - delta * 0.7);

}

void MapSpace::initBackground()
{
	backLayer = Sprite::create("space_background.png");
	auto backLayer_left = Sprite::create("space_background.png");
	auto backLayer_right = Sprite::create("space_background.png");
	backLayer_left->setFlippedX(true);
	backLayer_right->setFlippedX(true);
	initbackLayerPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	backLayer_left->setPosition(-backLayer->getContentSize().width / 2, backLayer->getContentSize().height / 2);
	backLayer_right->setPosition(backLayer->getContentSize().width *3 / 2, backLayer->getContentSize().height / 2);
	backLayer->addChild(backLayer_right, 0);
	backLayer->addChild(backLayer_left, 0);
	backLayer->setPosition(initbackLayerPosition);
	this->addChild(backLayer, 0);
	
	planet1 = Sprite::createWithSpriteFrameName("space_planet1.png");
	initPlanet1Position = Vec2(visibleSize.width / 2 + 1000, visibleSize.height / 2+300);
	planet1->setPosition(initPlanet1Position);
	this->addChild(planet1, 1);

	planet2 = Sprite::createWithSpriteFrameName("space_planet2.png");
	initPlanet2Position = Vec2(visibleSize.width / 2 - 1000, visibleSize.height / 2 + 500);
	planet2->setPosition(initPlanet2Position);
	this->addChild(planet2, 1);

	auto light = Sprite::create("light.png");
	light->setPosition(backLayer->getContentSize().width / 2 , backLayer->getContentSize().height / 2 );
	backLayer->addChild(light, 0);
	//
	platform = Sprite::createWithSpriteFrameName("space_floor.png");
	initPlatformPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	platform->setPosition(initPlatformPosition);
	this->addChild(platform, 2);

	platformSize = platform->getContentSize();

	auto support = Sprite::createWithSpriteFrameName("space_support.png");
	support->setPosition(platformSize.width/2, platformSize.height /2 -50);
	platform->addChild(support, 4);
}