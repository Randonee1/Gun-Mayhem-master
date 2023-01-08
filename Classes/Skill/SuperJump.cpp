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
	/*player->body->organ->stopAllActions();
	player->head->organ->stopAllActions();
	player->body->organ->setPosition(Vec2(0, 0));
	player->head->organ->setPosition(Vec2(0, 0));
	auto seq = Sequence::create(EaseSineOut::create(MoveBy::create(0.7, Vec2(0, -10))),
		EaseSineOut::create(MoveBy::create(0.7, Vec2(0, 10))), nullptr);
	auto rep = RepeatForever::create(seq);
	player->head->organ->runAction(rep);*/
}


void SuperJump::update(float dt)
{
	SkillBase::update(dt);

	if (storingPower && time < 2) {
		time += dt;
		speed += player->status->y_maxSpeed / 2 * dt;
	}

	if (player->inTheAir && player->y_speed == player->status->y_maxSpeed + player->status->gravitation *dt) {
		//CCLOG("first");
		//CCLOG("%d", player->floor);

		/*player->head->organ->stopAllActions();
		player->body->organ->runAction(EaseSineOut::create(MoveBy::create(1, Vec2(0, -20))));
		player->head->organ->runAction(EaseSineOut::create(MoveBy::create(1, Vec2(0, -20))));*/

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

		//CCLOG("other");
		/*player->body->organ->stopAllActions();
		player->head->organ->stopAllActions();
		player->body->organ->setPosition(Vec2(0, 0));
		player->head->organ->setPosition(Vec2(0, 0));
		auto seq = Sequence::create(EaseSineOut::create(MoveBy::create(0.7, Vec2(0, -10))),
			EaseSineOut::create(MoveBy::create(0.7, Vec2(0, 10))), nullptr);
		auto rep = RepeatForever::create(seq);
		player->head->organ->runAction(rep);*/

		storingPower = false;
		player->inTheAir = true;
		player->y_speed = speed;
		speed = player->status->y_maxSpeed;
		player->MoveDelay(true, false);
		player->DustUpdate();
	}
}
