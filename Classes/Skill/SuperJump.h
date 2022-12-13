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

	Spawn* HaloFade(Sprite* self);

	void update(float dt) override;

private:
	float y_maxSpeed;

	float halo_interval = 80;
	float halo_delta = 0;

	Halo* head;
	Halo* tail;
};

#endif