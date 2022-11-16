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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("test.plist");
	back = Sprite::createWithSpriteFrameName("bgd_weapontest_0.png");
	/*back = LayerColor::create(Color4B::GRAY, 12000, 10000);
	back->setIgnoreAnchorPointForPosition(false);
	back->setAnchorPoint(Vec2(0.5,0.5));*/
	back->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(back, 0);

	backgroundSize = back->getContentSize();

}

void MapTest::initPlayer()
{
	


	player1 = PlayerBase::createWithTag(1);
	player1->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	back->addChild(player1, 1);
	CCLOG("%f,%f", back->getContentSize().width / 2, back->getContentSize().height / 2);

	//test
	player2 = PlayerBase::createWithTag(2);
	player2 ->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	back->addChild(player2 , 2);
	//test

	
}
