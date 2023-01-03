#include "MapBase.h"
#include "Stuff/Package/PackageEvent.h"
#include "Sprite/CharacterBase.h"

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
}
