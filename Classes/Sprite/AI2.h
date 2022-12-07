#ifndef AI2_H
#define AI2_H

#include "cocos2d.h"
#include "Manager/GameManager.h"
#include "Weapons/Gun/Gun_Glock.h"
#include "AIBase.h"

USING_NS_CC;

class AI2 : public AIBase
{
public:

	static AI2* create(int tag, MapBase* map);

	bool init(int tag, MapBase* map);

	void initBody();
};

#endif