#ifndef SUPER_JUMP_H
#define SUPER_JUMP_H

#include "cocos2d.h"
#include "SkillBase.h"

USING_NS_CC;

struct Halo {
	Sprite* halo_back;
	Sprite* halo_front;
	Halo* next;

	Halo(Sprite* halo_back,Sprite* halo_front) {
		this->halo_back = halo_back;
		this->halo_front = halo_front;
		this->next = nullptr;
	}
};

class SuperJump : public SkillBase
{
public:
	SuperJump(CharacterBase* player);

	~SuperJump();

	void update(float dt) override;

private:

	bool storingPower;
	Vec2 headPosition;
	float time;
	float speed;
};

#endif