#include "ExtraLife.h"

ExtraLife::ExtraLife(CharacterBase* player)
{
	this->player = player;
	duration = 0;
	Duration = 1;
	if (player->Live <  UserManager::getInstance()->Live)
		player->Live++;

}

ExtraLife::~ExtraLife()
{
}
