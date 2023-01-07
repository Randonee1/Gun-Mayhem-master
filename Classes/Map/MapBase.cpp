#include "MapBase.h"
#include "Scene/PlayerSetup.h"
#include "Scene/AfterGame.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/CharacterBase.h"
#include "Sprite/AI2.h"
#include "Sprite/Player2.h"

bool MapBase::init()
{
	if (!Layer::init())
		return false;
	visibleSize = Director::getInstance()->getVisibleSize();

	packageEvent = PackageEvent::create(this);

	return true;
}

void MapBase::update(float dt)
{
	for (auto& player : players) {
		if (player->Live == 0) {
			GameOver(player);
		}
	}
	ShotEvent();
	packageEvent->update(dt);
	packageEvent->PackageUpdate(players);

}

void MapBase::ShotEvent()
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

				if (!(bullet->player->isDoppelganger && bullet->player->getTag() == player->getTag())) {
					bullet->player->hitCount++;

					player->x_speed += player->defense ? bullet->hitSpeed / 10 : bullet->hitSpeed;
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
}

void MapBase::initPlayer()
{
	auto manager = UserManager::getInstance();
	CharacterBase* player1;
	CharacterBase* player2;

	if (manager->player_type[1])
		player1 = Player2::createWithTag(1, this);
	else
		player1 = AI2::create(1, this);

	if (manager->player_type[2])
		player2 = Player2::createWithTag(2, this);
	else
		player2 = AI2::create(2, this);

	platform->addChild(player1, 1);
	platform->addChild(player2, 2);

	player1->GetOpponent(player2);
	player2->GetOpponent(player1);

	players.push_back(player1);
	players.push_back(player2);
}

bool MapBase::InTheBoundary(std::vector<float>& floor, float x) const
{
	for (int i = 0; i < floor.size() - 1; i += 2) {
		if (x > floor[i] && x < floor[i + 1])
			return true;
	}
	return false;
}

void MapBase::bindPlayerStateMenu(PlayerStateMenu* playerState)
{
	this->playerState = playerState;
	playerState->bindMap(this);
}

void MapBase::GameOver(CharacterBase* player)
{
	auto move = EaseSineOut::create(MoveTo::create(1, initPlatformPosition));
	auto delay = DelayTime::create(1);
	auto func = CallFunc::create([&]() {
		Director::getInstance()->replaceScene(Transition::create(0.5f, AfterGame::create()));
		});
	if(!gameOver)player->runAction(Sequence::create(move,delay, func, nullptr));
	gameOver = true;
}

