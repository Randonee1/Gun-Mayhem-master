#include "SuperJump.h"

SuperJump::SuperJump(CharacterBase* player)
{
	skillTpye = SUPER_JUMP;
	this->player = player;
	duration = 0;
	Duration = 10;
	

	storingPower = false;
	headPosition = Vec2(65 / 2.2 - 8, 130 / 2.2 - 2);
}

SuperJump::~SuperJump()
{
	
}


void SuperJump::update(float dt)
{
	SkillBase::update(dt);

	if (storingPower && time < 2) {
		time += dt;
		speed += player->status->y_maxSpeed / 2 * dt;
	}

	if (player->inTheAir && player->y_speed == player->status->y_maxSpeed + player->status->gravitation *dt) {
		
		time = 0;
		speed = player->status->y_maxSpeed;

		storingPower = true;
		player->inTheAir = false;
		
		player->floor = player->floor_actual;

		for (int i = 2; i < player->organs.size(); i++)
			player->organs[i]->stopActionByTag(player->organs[i]->lastDelayTag);
		player->MoveDelay(true, true);
		player->setPositionY(player->getPositionY() - player->y_speed*dt);
		player->y_speed = 0;
	}
	else if (storingPower && player->keyMap["release"]) {

		storingPower = false;
		player->inTheAir = true;
		player->y_speed = speed;
		speed = player->status->y_maxSpeed;
		player->MoveDelay(true, false);
		player->DustUpdate();
	}
}
