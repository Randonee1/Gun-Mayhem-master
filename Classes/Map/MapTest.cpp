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

	initPlayer();

	this->scheduleUpdate();

	return true;
}

void MapTest::update(float dt)
{
	/*if(delaytime>0.5)
	{*/
	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = (player1->getPosition() + player2->getPosition())/2 - initPlatform;

	/*delta.x > visibleSize.width ? delta.x = visibleSize.width : delta.x = delta.x;
	delta.y > visibleSize.height / 3 ? delta.y = visibleSize.height / 3 : delta.y = delta.y;
	delta.x < -visibleSize.width ? delta.x = -visibleSize.width : delta.x = delta.x;
	delta.y < -visibleSize.height / 3 ? delta.y = -visibleSize.height / 3 : delta.y = delta.y;*/

	float a = std::pow(delta.x, 2) + std::pow(delta.y, 2);
	float b = std::pow(visibleSize.height , 2) + std::pow(visibleSize.width , 2);
	if (a > b) {
		delta.x = delta.x * b / a;
		delta.y = delta.y * b / a;
	}

	//backLayer->runAction(MoveTo::create(delaytime, initbackLayerPosition - delta * 0.3));
	backLayer->setPosition(initbackLayerPosition - delta*0.3);
	//platform->runAction(MoveTo::create(delaytime, initPlatformPosition - delta * 0.4));
	platform->setPosition(initPlatformPosition - delta*0.4);
	

	ShotEvent();
}

void MapTest::initBackground()
{
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

void MapTest::initPlayer()
{
	
	player1 = Player1::createWithTag(1,this);
	platform->addChild(player1, 1);

	player2 = Player1::createWithTag(2, this);
	platform->addChild(player2, 2);
	//test
	/*player2 = Player_test::createWithTag(2, back);
	player2 ->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	back->addChild(player2 , 2);*/
	//test

	
}

void MapTest::ShotEvent()
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
	
	for (auto &bullet : bullets) {
		if (bullet->getBoundingBox().intersectsRect(rect1)) {
			bullet->isFlippedX() ? player1->x_speed -= 400 : player1->x_speed += 400;
			bullet->removeFromParent();
			bullet = nullptr;
			continue;
		}
		else if (bullet->getBoundingBox().intersectsRect(rect2)) {
			bullet->isFlippedX() ? player2->x_speed -= 400 : player2->x_speed += 400;
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
