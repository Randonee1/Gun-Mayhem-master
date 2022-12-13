#include "Defense.h"

Defense::Defense(CharacterBase* player, float time)
{
	this->player = player;
	duration = 0;
	Duration = time;
	player->defense = true;
	cover = Sprite::create("defense_bubble.png");
	player->addChild(cover, 100);
	auto delay = DelayTime::create(time-0.5);
	auto fade = FadeOut::create(0.5);
	auto seq = Sequence::create(delay, fade, nullptr);
	cover->runAction(seq);
}

Defense::~Defense()
{
	cover->removeFromParent();
	player->defense = false;
}
