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
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	initBackground();
	initPlayer();

	this->scheduleUpdate();

	return true;
}

void MapTest::update(float dt)
{
	float x = (visibleSize.width)/2 + (backgroundSize.width)/2 - (player1->getPositionX() + player2->getPositionX()+ backgroundSize.width) / 4;
	float y = (visibleSize.height)/2 + (backgroundSize.height)/2 - (player1->getPositionY() + player2->getPositionY() + backgroundSize.height) / 4;
	back->setPosition(Vec2(x, y));
}

void MapTest::initBackground()
{
	back = LayerColor::create(Color4B::GRAY, 12000, 10000);
	back->setIgnoreAnchorPointForPosition(false);
	back->setAnchorPoint(Vec2(0.5,0.5));
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(back, 1);

	backgroundSize = back->getContentSize();

}

void MapTest::initPlayer()
{
	player1 = PlayerBase::createWithTag(1);
	//player->setAnchorPoint(Vec2(0.5f, 0.5f));
	player1->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	back->addChild(player1, 0);

	//test
	player2 = PlayerBase::createWithTag(2);
	//player->setAnchorPoint(Vec2(0.5f, 0.5f));
	player2 ->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	back->addChild(player2 , 1);
	//test
}
