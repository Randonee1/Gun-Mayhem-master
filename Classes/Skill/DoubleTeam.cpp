#include "DoubleTeam.h"
#include "Sprite/AI2.h"

DoubleTeam::DoubleTeam(CharacterBase* player)
{
	this->player = player;
	duration = 0;
	Duration = 10;
	doppelganger = AI2::create(player->getTag(), player->map);
	doppelganger->isDoppelganger = true;
	doppelganger->playerName->setString("doppelganger");
	doppelganger->Live = 1;
	doppelganger->isDoubleJump = player->isDoubleJump;
	doppelganger->inTheAir = player->inTheAir;
	doppelganger->floor = player->floor;
	doppelganger->floor_actual = player->floor_actual;
	if (doppelganger->skill) { delete doppelganger->skill; doppelganger->skill = nullptr; }

	doppelganger->Flip(player->isFlippedX());
	doppelganger->GetOpponent(player->opponent);
	doppelganger->setPosition(player->getPosition());
	player->map->platform->addChild(doppelganger);
}

DoubleTeam::~DoubleTeam()
{
	if (doppelganger->gun->gunshadow_right)
		doppelganger->gun->gunshadow_right->removeFromParent();
	doppelganger->removeFromParent();
	doppelganger = nullptr;
}

void DoubleTeam::update(float dt)
{
	SkillBase::update(dt);
	if (doppelganger->Live == 0)
		duration = 10;
	ShotEvent();
}

void DoubleTeam::ShotEvent()
{

	std::vector<Bullet*> temp;
	for (auto bullet : player->map->bullets) {
		if (bullet)
			temp.push_back(bullet);
	}
	player->map->bullets = temp;

	for (auto& bullet : player->map->bullets) {

		auto rect = doppelganger->body->organ->getBoundingBox();
		Vec2 offset = doppelganger->getPosition() + doppelganger->body->getPosition();
		rect.origin += offset;

		if (rect.containsPoint(bullet->getPosition()) && doppelganger->valid && 
			bullet->player->getTag()!=doppelganger->getTag()) {

			doppelganger->x_speed +=  bullet->hitSpeed;
			doppelganger->hit = true;
			auto blood = Blood::create();
			blood->setPosition(bullet->getPosition());
			player->map->platform->addChild(blood, 4);

			bullet->removeFromParent();
			bullet = nullptr;
			break;
		}
	}
}
