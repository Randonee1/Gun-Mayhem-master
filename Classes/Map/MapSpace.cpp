#include "MapSpace.h"

MapBase* MapSpace::createGame()
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
	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = (player1->getPosition() + player2->getPosition()) / 2 - initPlatform;

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


	ShotEvent();
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

void MapSpace::initPlayer()
{
	player1 = Player1::createWithTag(1,this);
	platform->addChild(player1, 1);

	/*player2 = Player1::createWithTag(2, this);
	platform->addChild(player2, 2);

	player1 = AI1::create(this);
	platform->addChild(player1, 1);*/

	player2 = AI1::create(this);
	platform->addChild(player2, 2);

	player1->GetOpponent(player2);
	player2->GetOpponent(player1);
}

void MapSpace::ShotEvent()
{
	auto rect1 = player1->body->organ->getBoundingBox();
	Vec2 offset1 = player1->getPosition() + player1->body->getPosition();
	rect1.origin += offset1;

	auto rect2 = player2->body->organ->getBoundingBox();
	Vec2 offset2 = player2->getPosition() + player2->body->getPosition();
	rect2.origin += offset2;

	std::vector<Bullet*> temp;
	for (auto bullet : bullets) {
		if (bullet)
			temp.push_back(bullet);
	}
	bullets = temp;

	for (auto& bullet : bullets) {
		if (rect1.containsPoint(bullet->getPosition())) {
			player1->x_speed += bullet->speed /2;
			player1->hit = true;
			auto blood = Blood::create();
			blood->setPosition(bullet->getPosition());
			platform->addChild(blood, 4);

			bullet->removeFromParent();
			bullet = nullptr;
			continue;
		}
		else if (rect2.containsPoint(bullet->getPosition())) {
			player2->x_speed += bullet->speed / 2;
			player2->hit = true;
			auto blood = Blood::create();
			blood->setPosition(bullet->getPosition());
			platform->addChild(blood, 4);

			bullet->removeFromParent();
			bullet = nullptr;
			continue;
		}
		else if (bullet->getPositionX() > 12000 || bullet->getPositionX() < -6000) {
			bullet->removeFromParent();
			bullet = nullptr;
			continue;
		}
	}
}
