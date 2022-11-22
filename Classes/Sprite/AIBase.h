#ifndef AI_BASE_H
#define AI_BASE_H

#include "cocos2d.h"
#include "CharacterBase.h"

USING_NS_CC;

class AIBase : public CharacterBase
{
public:

	bool init(MapBase* map);

	virtual void initBody();

	void update(float dt) override;

	void MoveEvent();

	void ShotEvent();


protected:

};

#endif