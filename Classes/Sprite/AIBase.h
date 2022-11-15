#ifndef AI_BASE_H
#define AI_BASE_H

#include "cocos2d.h"
#include "Body/Body.h"
#include "Body/Face.h"
#include "Body/Foot.h"
#include "Body/Hand.h"
#include "Body/Head.h"
#include "Weapons/Gun/GunBase.h"

USING_NS_CC;

class AIBase : public Sprite
{
public:

	bool init() override;

	CREATE_FUNC(AIBase);

	void update(float dt) override;
};

#endif