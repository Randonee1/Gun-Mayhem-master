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
	Vec2 delta = player1->getPosition() - initPlatform;

	delta.x > visibleSize.width / 3 ? delta.x = visibleSize.width / 3 : delta.x = delta.x;
	delta.y > visibleSize.height / 3 ? delta.y = visibleSize.height / 3 : delta.y = delta.y;
	delta.x < -visibleSize.width / 3 ? delta.x = -visibleSize.width / 3 : delta.x = delta.x;
	delta.y < -visibleSize.height / 3 ? delta.y = -visibleSize.height / 3 : delta.y = delta.y;

	//backLayer->runAction(MoveTo::create(delaytime, initbackLayerPosition - delta * 0.3));
	backLayer->setPosition(initbackLayerPosition - delta*0.3);
	//platform->runAction(MoveTo::create(delaytime, initPlatformPosition - delta * 0.4));
	platform->setPosition(initPlatformPosition - delta*0.4);
	/*float x = (visibleSize.width)/2 + (backgroundSize.width)/2 - (player1->getPositionX() + player2->getPositionX()+ backgroundSize.width) / 4;
	float y = (visibleSize.height)/2 + (backgroundSize.height)/2 - (player1->getPositionY() + player2->getPositionY() + backgroundSize.height) / 4;
	back->setPosition(Vec2(x, y));*/
	/*	delaytime = 0;
	}
	else
		delaytime += dt;*/
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
	//test
	/*player2 = Player_test::createWithTag(2, back);
	player2 ->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	back->addChild(player2 , 2);*/
	//test

	
}
