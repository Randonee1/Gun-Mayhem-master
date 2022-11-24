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
	CharacterBase* player1 = Player1::createWithTag(1, this);
	platform->addChild(player1, 1);

	/*CharacterBase* player1 = AI1::create(this);
	platform->addChild(player1, 1);

	CharacterBase* player2 = AI1::create(this);
	platform->addChild(player2, 2);*/

	CharacterBase* player2 = Player1::createWithTag(2, this);
	platform->addChild(player2, 2);

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

	bool land1 = false;
	for (auto player : players) {
		if (!player->inTheAir && player->floor == 1 &&
			Floor[1][0] < player->getPositionX() &&
			player->getPositionX() < Floor[1][1]) {
			if (!eyes[1]->isVisible()) {
				eyes[1]->setVisible(true);
				auto fadein = FadeIn::create(0.3);
				eyes[1]->runAction(fadein);
			}
			land1 = true;
			break;
		}
	}
	if (!land1 && eyes[1]->isVisible() && eyes[1]->getOpacity() == 255) {
		CallFunc* fade = CallFunc::create([&]() {
			eyes[1]->setVisible(false);
			});
		auto fadeout = FadeOut::create(0.3);
		eyes[1]->runAction(Sequence::create(fadeout, fade, nullptr));
	}
	bool land2 = false;
	for (auto player : players) {
		if (!player->inTheAir && player->floor == 1 &&
			Floor[1][2] < player->getPositionX() &&
			player->getPositionX() < Floor[1][3]) {
			if (!eyes[2]->isVisible()) {
				eyes[2]->setVisible(true);
				auto fadein = FadeIn::create(0.3);
				eyes[2]->runAction(fadein);
			}
			land2 = true;
			break;
		}
	}
	if (!land2 && eyes[2]->isVisible() && eyes[2]->getOpacity() == 255) {
		CallFunc* fade = CallFunc::create([&]() {
			eyes[2]->setVisible(false);
			});
		auto fadeout = FadeOut::create(0.3);
		eyes[2]->runAction(Sequence::create(fadeout, fade, nullptr));
	}

	bool land3 = false;
	for (auto player : players) {
		if (!player->inTheAir && player->floor == 2 &&
			Floor[2][0] < player->getPositionX() &&
			player->getPositionX() < Floor[2][1]) {
			if (!eyes[3]->isVisible()) {
				eyes[3]->setVisible(true);
				auto fadein = FadeIn::create(0.3);
				eyes[3]->runAction(fadein);
			}
			land3 = true;
			break;
		}
	}
	if (!land3 && eyes[3]->isVisible() && eyes[3]->getOpacity() == 255) {
		CallFunc* fade = CallFunc::create([&]() {
			eyes[3]->setVisible(false);
			});
		auto fadeout = FadeOut::create(0.3);
		eyes[3]->runAction(Sequence::create(fadeout, fade, nullptr));
	}

	bool land4 = false;
	for (auto player : players) {
		if (!player->inTheAir && player->floor == 2 &&
			Floor[2][2] < player->getPositionX() &&
			player->getPositionX() < Floor[2][3]) {
			if (!eyes[4]->isVisible()) {
				eyes[4]->setVisible(true);
				auto fadein = FadeIn::create(0.3);
				eyes[4]->runAction(fadein);
			}
			land4 = true;
			break;
		}
	}
	if (!land4 && eyes[4]->isVisible() && eyes[4]->getOpacity() == 255) {
		CallFunc* fade = CallFunc::create([&]() {
			eyes[4]->setVisible(false);
			});
		auto fadeout = FadeOut::create(0.3);
		eyes[4]->runAction(Sequence::create(fadeout, fade, nullptr));
	}

	bool land5 = false;
	for (auto player : players) {
		if (!player->inTheAir && player->floor == 3 &&
			Floor[3][0] < player->getPositionX() &&
			player->getPositionX() < Floor[3][1]) {
			if (!eyes[5]->isVisible()) {
				eyes[5]->setVisible(true);
				auto fadein = FadeIn::create(0.3);
				eyes[5]->runAction(fadein);
			}
			land5 = true;
			break;
		}
	}
	if (!land5 && eyes[5]->isVisible() && eyes[5]->getOpacity() == 255) {
		CallFunc* fade = CallFunc::create([&]() {
			eyes[5]->setVisible(false);
			});
		auto fadeout = FadeOut::create(0.3);
		eyes[5]->runAction(Sequence::create(fadeout, fade, nullptr));
	}

	bool land6 = false;
	for (auto player : players) {
		if (!player->inTheAir && player->floor == 3 &&
			Floor[3][2] < player->getPositionX() &&
			player->getPositionX() < Floor[3][3]) {
			if (!eyes[6]->isVisible()) {
				eyes[6]->setVisible(true);
				auto fadein = FadeIn::create(0.3);
				eyes[6]->runAction(fadein);
			}
			land6 = true;
			break;
		}
	}
	if (!land6 && eyes[6]->isVisible() && eyes[6]->getOpacity() == 255) {
		CallFunc* fade = CallFunc::create([&]() {
			eyes[6]->setVisible(false);
			});
		auto fadeout = FadeOut::create(0.3);
		eyes[6]->runAction(Sequence::create(fadeout, fade, nullptr));
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
