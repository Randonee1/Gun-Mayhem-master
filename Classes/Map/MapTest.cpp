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

	initPackage();

	this->scheduleUpdate();

	return true;
}

void MapTest::update(float dt)
{
	
	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = Vec2(0, 0);
	for (auto& player : players) { delta += player->getPosition(); }
	delta = delta / players.size() - initPlatform;

	float a = std::pow(delta.x, 2) + std::pow(delta.y, 2);
	float b = std::pow(visibleSize.height/1.2 , 2) + std::pow(visibleSize.width/1.2 , 2);
	if (a > b) {
		delta.x = delta.x * b / a;
		delta.y = delta.y * b / a;
	}

	backLayer->setPosition(initbackLayerPosition - delta*0.5);
	platform->setPosition(initPlatformPosition - delta*0.7);
	

	ShotEvent();

	PackageEvent();
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
	
	auto player1 = Player1::createWithTag(1,this);
	platform->addChild(player1, 1);

	auto player2 = Player1::createWithTag(2, this);
	platform->addChild(player2, 2);

	//test
	/*player2 = Player_test::createWithTag(2, back);
	player2 ->setPosition(back->getContentSize().width / 2, back->getContentSize().height / 2);
	back->addChild(player2 , 2);*/
	//test
	
	/*player1 = AI1::create(this);
	platform->addChild(player1, 1);

	player2 = AI1::create(this);
	platform->addChild(player2, 2);

	player1->GetOpponent(player2);
	player2->GetOpponent(player1);*/

	players.push_back(player1);
	players.push_back(player2);

}

void MapTest::initPackage()
{
	auto package_gun_1 = GunPackage::createWithGun(this);
	packages.push_back(package_gun_1);
}

void MapTest::ShotEvent()
{
	std::vector<Bullet*> temp;
	for (auto bullet : bullets) {
		if (bullet)
			temp.push_back(bullet);
	}
	bullets = temp;

	for (auto& bullet : bullets) {

		if (bullet->getPositionX() > 12000 || bullet->getPositionX() < -6000) {
			bullet->removeFromParent();
			bullet = nullptr;
			continue;
		}
		for (auto& player : players) {

			auto rect = player->body->organ->getBoundingBox();
			Vec2 offset = player->getPosition() + player->body->getPosition();
			rect.origin += offset;

			if (rect.containsPoint(bullet->getPosition())) {
				player->x_speed += bullet->hitSpeed;
				player->hit = true;
				auto blood = Blood::create();
				blood->setPosition(bullet->getPosition());
				platform->addChild(blood, 4);

				bullet->removeFromParent();
				bullet = nullptr;
				break;
			}
		}
	}
}

void MapTest::PackageEvent()
{
	std::vector<PackageBase* > temp;
	for (auto package : packages) {
		if (package)
			temp.push_back(package);
	}
	packages = temp;
	
	for (auto& package : packages) {

		if (package->getPositionY() < death_line) {
			package->removeFromParent();
			package = nullptr;
			continue;
		}
		for (auto& player : players) {
			auto rect = player->body->organ->getBoundingBox();
			Vec2 offset = player->getPosition() + player->body->getPosition();
			rect.origin += offset;

			if (rect.containsPoint(package->getPosition())) {

				package->GetPackage(player);

				package->removeFromParent();
				package = nullptr;

				//添加一个消失动画

				break;
			}
		}

	}

}
