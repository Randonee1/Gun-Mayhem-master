#include "SpeedUp.h"

SpeedUp::SpeedUp(CharacterBase* player)
{

	this->player = player;
	duration = 0;
	Duration = 10;

	acceleration = player->status->acceleration;
	x_maxSpeed = player->status->x_maxSpeed;

	player->status->acceleration *= 2;
	player->status->x_maxSpeed *= 2;

	
	head = nullptr;
	tail = nullptr;
}

SpeedUp::~SpeedUp()
{
	player->status->acceleration = acceleration;
	player->status->x_maxSpeed = x_maxSpeed;
	while (tail) {
		if (tail->figure)
			tail->figure->removeFromParent();
		tail = tail->next;
	}
}



Sprite* SpeedUp::Figure(Shadow* shadow, float ocpacity)
{
	for (auto& child : shadow->figure->getChildren())
	{
		for(auto& c : child->getChildren())
			c->setOpacity(ocpacity);
		child->setOpacity(ocpacity);
	}
	shadow->figure->setOpacity(ocpacity);
	return shadow->figure;
}

void SpeedUp::update(float dt)
{
	SkillBase::update(dt);

	if(shadow_deltatime > shadow_interval)
	{

		
		if (head != nullptr) {
			head->next = new Shadow(player->clone(), player->getPosition(), head);
			//auto figure = Figure(head, 50);
			head->figure->setPosition(head->point);
			player->map->platform->addChild(head->figure, 0);
			head = head->next;

			float opacity = 60;
			Shadow* ptr = head->last;
			while (ptr) {
				ptr->figure = Figure(ptr, opacity);
				opacity -= 10;
				ptr = ptr->last;
			}

			if (shadow_number < shadow_size) {
				shadow_number++;
			}
			else {
				tail = tail->next;
				tail->last->figure->removeFromParent();
				delete tail->last;
				tail->last = nullptr;
			}
		}
		else {
			head =new Shadow(player->clone(), player->getPosition(), nullptr);
			tail = head;
		}

		shadow_deltatime = 0;
	}
	else {
		shadow_deltatime += dt;
	}
	
}
