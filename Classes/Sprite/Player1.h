#ifndef PLAYER1_H
#define PLAYER1_H

#include "cocos2d.h"
#include "PlayerBase.h"

USING_NS_CC;

class Player1 : public PlayerBase
{
public:

	static Player1* createWithTag(int name, Sprite* background);

	bool initWithTag(int name, Sprite* background);

	void initBody();
};

#endif