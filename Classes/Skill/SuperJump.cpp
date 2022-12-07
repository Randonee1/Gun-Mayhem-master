#include "SuperJump.h"

SuperJump::SuperJump(CharacterBase* player)
{
	this->player = player;
	duration = 0;
	Duration = 10;

	y_maxSpeed = player->status->y_maxSpeed;

	player->status->y_maxSpeed *= 2;

	head = nullptr;
	tail = nullptr;
}

SuperJump::~SuperJump()
{

	while (head) {
		Halo* temp = head;
		head = head->next;
		delete temp;
		temp = nullptr;
	}
	player->status->y_maxSpeed = y_maxSpeed;
}

Spawn* SuperJump::HaloFade(Sprite* self)
{
	auto fade = FadeOut::create(0.1);
	auto shrink = ScaleBy::create(0, 0.1);
	auto enlarge = ScaleBy::create(0.15, 2);
	CallFunc* remove = CallFunc::create([self]() {self->setVisible(false); });
	auto seq = Sequence::create(enlarge,remove,nullptr);
	return Spawn::create(seq,nullptr);
}

void SuperJump::update(float dt)
{
	SkillBase::update(dt);

	while (head != nullptr) {
		if (!head->halo_back->isVisible()) {
			Halo* temp = head;
			head = head->next;
			temp->halo_back->stopAllActions();
			temp->halo_front->stopAllActions();
			delete temp;
			temp = nullptr;
		}
		else
			break;
	}

	Halo* ptr = head;
	
	while (ptr != nullptr) {
		ptr->halo_back->setPositionX(player->getPositionX());
		ptr->halo_front->setPositionX(player->getPositionX());
		ptr = ptr->next;
	}

	if(player->y_speed > 0)
	{
		if (halo_delta > halo_interval) {
			Sprite* halo_back = Sprite::createWithSpriteFrameName("jumphaloback.png");
			Sprite* halo_front = Sprite::createWithSpriteFrameName("jumphalofront.png");
			/*halo_back->setScale(0.5);
			halo_front->setScale(0.5);*/
			Vec2 point = player->getPosition();
			point.y += 50;

			halo_back->setPosition(point);
			halo_front->setPosition(point);
			player->map->platform->addChild(halo_back, 0);
			player->map->platform->addChild(halo_front, player->getTag());
			halo_back->runAction(HaloFade(halo_back));
			halo_front->runAction(HaloFade(halo_front));

			if (head) {
				tail->next = new Halo(halo_back, halo_front);
				tail = tail->next;
			}
			else {
				head = new Halo(halo_back, halo_front);
				tail = head;
			}


			halo_delta = 0;
		}
		else {
			halo_delta += player->y_speed * dt;
		}
	}
	else
		halo_delta = 0;
}
