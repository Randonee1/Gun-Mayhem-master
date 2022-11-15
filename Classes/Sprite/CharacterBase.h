#ifndef CHARACTER_BASE_H
#define CHARACTER_BASE_H

#include "cocos2d.h"
#include "Organ/Body.h"
#include "Organ/Face.h"
#include "Organ/Foot.h"
#include "Organ/Hand.h"
#include "Organ/Head.h"
#include "Weapons/Gun/GunBase.h"

USING_NS_CC;

class CharacterBase : public Sprite
{
public:

	bool init() override;

	CREATE_FUNC(CharacterBase);
};

#endif