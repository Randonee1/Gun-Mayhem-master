#ifndef	PLAYER_TEST_H
#define PLAYER_TEST_H

#include "cocos2d.h"
#include "PlayerBase.h"

USING_NS_CC;

class Player_test : public PlayerBase
{
public:
	static Player_test* createWithTag(int name, Sprite* background);

	bool initWithTag(int name, Sprite* background);

	void initBody();
	
};

#endif