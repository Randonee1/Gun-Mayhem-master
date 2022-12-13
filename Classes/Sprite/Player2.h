#ifndef PLAYER2_H
#define PLAYER2_H

#include "cocos2d.h"
#include "PlayerBase.h"
#include "Weapons/Gun/Gun_Glock.h"

USING_NS_CC;

class Player2 : public PlayerBase
{
public:

	static Player2* createWithTag(int name, MapBase* map);

	bool initWithTag(int name, MapBase* map);

	void initBody();
};

#endif