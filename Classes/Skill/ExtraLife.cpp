#include "ExtraLife.h"

ExtraLife::ExtraLife(CharacterBase* player)
{
	skillTpye = EXTRA_LIFE;
	this->player = player;
	duration = 0;
	Duration = 1;
	if (player->Live <  UserManager::getInstance()->Live)
		player->Live++;

}

ExtraLife::~ExtraLife()
{
}
