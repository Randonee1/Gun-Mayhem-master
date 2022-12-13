#include "Jetpack.h"

Jetpack::Jetpack(CharacterBase* player)
{
	this->player = player;
	duration = 0;
	Duration = 10;

	gravitation = player->status->gravitation;
	anti_gravitation = -player->status->gravitation*2;
}

Jetpack::~Jetpack()
{
	player->status->gravitation = gravitation;
}

void Jetpack::update(float dt)
{
	SkillBase::update(dt);


	if (player->keyMap["up"] == true && player->inTheAir && player->isDoubleJump) {
		if (onAction)
			player->MoveDelay(true, false);
		onAction = false;
		player->status->gravitation = anti_gravitation;
		if (player->y_speed > player->status->y_maxSpeed/1.2)
			player->y_speed -= player->status->gravitation * dt;
	}
	else {
		player->status->gravitation = gravitation;
		onAction = true;
	}

}
