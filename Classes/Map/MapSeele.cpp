#include "MapSeele.h"

MapSeele* MapSeele::createGame()
{
	auto layer = new MapSeele();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return NULL;
}

bool MapSeele::init()
{
	if (!MapBase::init()) {
		return false;
	}
	initBackground();

	floor_height = 260;
	floor_base = 150;
	Floor = { {812,1459},{0,654,812,1459},{0,654,812,1459},{0,654,812,1459} };
	death_line = -1000;


	initPlayer();

	packageEvent = PackageEvent::create(this);

	this->scheduleUpdate();

	return true;
}

void MapSeele::update(float dt)
{
	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = Vec2(0, 0);
	for (auto& player : players) { delta += player->getPosition(); }
	delta = delta / players.size() - initPlatform;

	float a = std::pow(delta.x, 2) + std::pow(delta.y, 2);
	float b = std::pow(visibleSize.height / 1.5, 2) + std::pow(visibleSize.width / 1.5, 2);
	if (a > b) {
		delta.x = delta.x * b / a;
		delta.y = delta.y * b / a;
	}

	backLayer->setPosition(initbackLayerPosition - delta * 0.5);
	seele->setPosition(initSeelePosition - delta * 0.6);
	platform->setPosition(initPlatformPosition - delta * 0.7);

	EyeBlink();

	ShotEvent();

	packageEvent->update(dt);
	packageEvent->PackageUpdate(players);
}

void MapSeele::initBackground()
{
	backLayer = Sprite::create("seele/background.png");
	initbackLayerPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	backLayer->setPosition(initbackLayerPosition);
	this->addChild(backLayer, 0);

	seele = Sprite::create("seele/seele.png");
	initSeelePosition = Vec2(visibleSize.width / 2 - 550, visibleSize.height / 2 - 500);
	seele->setPosition(initSeelePosition);
	this->addChild(seele, 0);

	platform = Sprite::create("seele/platform.png");
	initPlatformPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	platform->setPosition(initPlatformPosition);
	this->addChild(platform, 1);
	platformSize = platform->getContentSize();

	initEyes();
}

void MapSeele::initPlayer()
{
	/*CharacterBase* player1 = Player1::createWithTag(1, this);
	platform->addChild(player1, 1);*/

	CharacterBase* player1 = AI1::create(this);
	platform->addChild(player1, 1);

	CharacterBase* player2 = AI1::create(this);
	platform->addChild(player2, 2);

	/*CharacterBase* player2 = Player1::createWithTag(2, this);
	platform->addChild(player2, 2);*/

	player1->GetOpponent(player2);
	player2->GetOpponent(player1);

	players.push_back(player1);
	players.push_back(player2);
}

void MapSeele::initEyes()
{
	auto eye0 = Sprite::create("seele/eye.png");
	eye0->setPosition(1132, 70);
	eye0->setVisible(false);
	platform->addChild(eye0, 0);
	eyes.push_back(eye0);

	auto eye1 = Sprite::create("seele/eye.png");
	eye1->setPosition(327, 330);
	eye1->setVisible(false);
	platform->addChild(eye1, 0);
	eyes.push_back(eye1);

	auto eye2 = Sprite::create("seele/eye.png");
	eye2->setPosition(1132, 330);
	eye2->setVisible(false);
	platform->addChild(eye2, 0);
	eyes.push_back(eye2);

	auto eye3 = Sprite::create("seele/eye.png");
	eye3->setPosition(327, 590);
	eye3->setVisible(false);
	platform->addChild(eye3, 0);
	eyes.push_back(eye3);

	auto eye4 = Sprite::create("seele/eye.png");
	eye4->setPosition(1132, 590);
	eye4->setVisible(false);
	platform->addChild(eye4, 0);
	eyes.push_back(eye4);

	auto eye5 = Sprite::create("seele/eye.png");
	eye5->setPosition(327, 850);
	eye5->setVisible(false);
	platform->addChild(eye5, 0);
	eyes.push_back(eye5);

	auto eye6 = Sprite::create("seele/eye.png");
	eye6->setPosition(1132, 850);
	eye6->setVisible(false);
	platform->addChild(eye6, 0);
	eyes.push_back(eye6);
}

void MapSeele::EyeBlink()
{
	
	bool land0 = false;
	for (auto player : players) {
		if (!player->inTheAir && player->floor == 0 && 
			Floor[0][0] < player->getPositionX() && 
			player->getPositionX() < Floor[0][1]) {
			if (!eyes[0]->isVisible()) {
				eyes[0]->setVisible(true);
				auto fadein = FadeIn::create(0.3);
				eyes[0]->runAction(fadein);
			}
			land0 = true;
			break;
		}
	}
	if (!land0 && eyes[0]->isVisible()) {
		CallFunc* fade = CallFunc::create([&]() {
			eyes[0]->setVisible(false);
			});
		auto fadeout = FadeOut::create(0.3);
		eyes[0]->runAction(Sequence::create(fadeout, fade,nullptr));
	}


	for (int i = 1; i < eyes.size(); i++) {
		bool land = false;
		for (auto player : players) {
			if (!player->inTheAir && player->floor == (i + 1)/2 &&
				Floor[(i + 1) / 2][((i + 1) % 2) * 2] < player->getPositionX() &&
				player->getPositionX() < Floor[(i + 1) / 2][((i + 1) % 2) * 2 + 1]) {
				if (!eyes[i]->isVisible()) {
					eyes[i]->setVisible(true);
					auto fadein = FadeIn::create(0.3);
					eyes[i]->runAction(fadein);
				}
				land = true;
				break;
			}
		}
		if (!land && eyes[i]->isVisible() && eyes[i]->getOpacity() == 255) {
			CallFunc* fade = CallFunc::create([&,i]() {
				eyes[i]->setVisible(false);
				});
			auto fadeout = FadeOut::create(0.3);
			eyes[i]->runAction(Sequence::create(fadeout, fade, nullptr));
		}
	}

}

void MapSeele::ShotEvent()
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

			if (rect.containsPoint(bullet->getPosition()) && player->valid) {
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
