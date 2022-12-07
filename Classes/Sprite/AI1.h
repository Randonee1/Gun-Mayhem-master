#ifndef AI1_H
#define AI1_H

#include "cocos2d.h"
#include "AIBase.h"
#include "Weapons/Gun/Gun_Glock.h"
#include "Weapons/Gun/Gun_MG_P90.h"

USING_NS_CC;

class AI1 : public AIBase
{
public:

	static AI1* create(int tag, MapBase* map);

	bool init(int tag, MapBase* map);

	void initBody();
};

#endif