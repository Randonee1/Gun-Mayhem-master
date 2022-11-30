#include "SpeedUp.h"

SpeedUp::SpeedUp(CharacterBase* player)
{

	this->player = player;
	duration = 0;
	Duration = 10;

	acceleration = player->status->acceleration;
	x_maxSpeed = player->status->x_maxSpeed;

	player->status->acceleration *= 1.4;
	player->status->x_maxSpeed *= 2;

	head = new Shadow(player->getPosition(), nullptr);
	tail = head;
	shadow_number ++;

}

SpeedUp::~SpeedUp()
{
	player->status->acceleration = acceleration;
	player->status->x_maxSpeed = x_maxSpeed;
	head_figure->removeFromParent();
}

Sprite* SpeedUp::Figure(CharacterBase* player)
{
	Sprite* body = Sprite::createWithSpriteFrameName(player->body->name);
	Sprite* head = Sprite::createWithSpriteFrameName(player->head->name);
	Sprite* hand1 = Sprite::createWithSpriteFrameName(player->hand1->name);
	Sprite* hand2 = Sprite::createWithSpriteFrameName(player->hand2->name);
	Sprite* foot1 = Sprite::createWithSpriteFrameName(player->feet1->name);
	Sprite* foot2 = Sprite::createWithSpriteFrameName(player->feet2->name);

	body->setOpacity(100);
	head->setOpacity(100);
	hand1->setOpacity(100);
	hand2->setOpacity(100);
	foot1->setOpacity(100);
	foot2->setOpacity(100);

	if(! player->isFlippedX()) {
		
		Vec2 origin = body->getContentSize() / 2;

		head->setPosition(Vec2(65 / 2.2 - 8, 130 / 2.2 - 2) + origin);
		body->addChild(head, 0);

		hand1->setPosition(Vec2(-31 / 2.2, -55 / 2.2) + origin);
		body->addChild(hand1, 0);

		hand2->setPosition(Vec2(109 / 2.2, -29 / 2.2) + origin);
		body->addChild(hand2, -1);

		foot1->setPosition(Vec2(-67 / 2.2, -199 / 2.2) + origin);
		foot1->setAnchorPoint(Vec2(0.2, 0.2));
		body->addChild(foot1, 0);

		foot2->setPosition(Vec2(33 / 2.2, -169 / 2.2) + origin);
		foot2->setAnchorPoint(Vec2(0.2, 0.2));
		body->addChild(foot2, -1);

		
	}
	else {
		Vec2 origin = body->getContentSize() / 2;
		head->setFlippedX(true);
		head->setPosition(Vec2(-65 / 2.2 + 8, 130 / 2.2 - 2) + origin);
		body->addChild(head, 0);

		hand1->setPosition(Vec2(31 / 2.2, -55 / 2.2) + origin);
		body->addChild(hand1, 0);

		hand2->setPosition(Vec2(-109 / 2.2, -29 / 2.2) + origin);
		body->addChild(hand2, -1);

		foot1->setFlippedX(true);
		foot1->setPosition(Vec2(67 / 2.2, -199 / 2.2) + origin);
		foot1->setAnchorPoint(Vec2(0.8, 0.2));
		body->addChild(foot1, 0);

		foot2->setFlippedX(true);
		foot2->setPosition(Vec2(-33 / 2.2, -169 / 2.2) + origin);
		foot2->setAnchorPoint(Vec2(0.8, 0.2));
		body->addChild(foot2, -1);

		body->setFlippedX(true);
		body->setOpacity(100);
	}
	return body;
}

void SpeedUp::update(float dt)
{
	SkillBase::update(dt);

	if(shadow_deltatime > shadow_interval)
	{

		if (head_figure)
		{
			head_figure->removeFromParent();

			head->next = new Shadow(player->getPosition(), head);
			head = head->next;

			if (shadow_number < shadow_size) {
				shadow_number++;
			}
			else {
				tail = tail->next;
				delete tail->last;
				tail->last = nullptr;
			}
		}

		tail = head;
		head_figure = Figure(player);
		next_figure = head_figure;
		next_figure->setPosition(head->point - player->getPosition());
		player->addChild(next_figure, -1);

		while (tail->last != nullptr) {
			Vec2 delta = tail->last->point - tail->point;
			tail = tail->last;
			last_figure = Figure(player);
			last_figure->setPosition(delta+next_figure->getContentSize()/2);
			next_figure->addChild(last_figure, -1);
			next_figure = last_figure;
		}
		shadow_deltatime = 0;
	}
	else {
		shadow_deltatime += dt;
	}
	
}
