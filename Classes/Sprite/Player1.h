#ifndef PLAYER1_H
#define PLAYER1_H

#include "cocos2d.h"
#include "PlayerBase.h"
#include "Weapons/Gun/Gun_Glock.h"
#include "Weapons/Gun/Gun_MG_P90.h"

USING_NS_CC;

class Player1 : public PlayerBase
{
public:

	static Player1* createWithTag(int name, MapBase* map);

	bool initWithTag(int name, MapBase* map);

	void initBody();
	
};

#endif