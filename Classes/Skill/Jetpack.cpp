#include "Jetpack.h"

Jetpack::Jetpack(CharacterBase* player)
{
	skillTpye = JETPACK;
	this->player = player;
	duration = 0;
	Duration = 10;

	gravitation = player->status->gravitation;
	anti_gravitation = -player->status->gravitation*2;

	jetpack = Sprite::create("jetpack.png");
	Vec2 position = player->isFlippedX() ? Vec2(30, 30) : Vec2(-30, 30);
	jetpack->setPosition(position);
	jetpack->setFlippedX(player->isFlippedX());
	player->addChild(jetpack, -1);

}

Jetpack::~Jetpack()
{
	player->status->gravitation = gravitation;
	jetpack->removeFromParent();
	jetpack = nullptr;
}

void Jetpack::Emission()
{
	for (auto& exhaust : Exhaust) {
		if (!exhaust->isVisible()) {
			exhaust->removeFromParent();
			exhaust = nullptr;
		}
	}
	std::vector<Sprite*> temp;
	for (auto exhaust : Exhaust) {
		if (exhaust)
			temp.push_back(exhaust);
	}
	Exhaust = temp;

	auto exhaust = Sprite::createWithSpriteFrameName("5.png");
	Vec2 point = player->getPosition() + jetpack->getPosition() +
		(jetpack->isFlippedX() ? Vec2(25, -70) : Vec2(-25, -70));
	exhaust->setPosition(point);
	Exhaust.push_back(exhaust);
	player->map->platform->addChild(exhaust, 5);

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(5);
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("5.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("4.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("3.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("2.png"));
	animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("1.png"));

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	float y = GameManager::Random(-20, 150) - (player->y_speed * 0.5)/3;
	float x = GameManager::Random(-100, 100)+ player->x_speed*0.5/2;
	auto move = EaseSineOut::create(MoveBy::create(0.5f, Vec2(x, -y)));
	auto shrink = ScaleBy::create(0.5f, 0);
	auto disappear = CallFunc::create([exhaust]() {exhaust->setVisible(false); });
	auto seq = Sequence::create(move, disappear, nullptr);
	auto spa = Spawn::create(seq, shrink, animate->clone(), nullptr);
	
	exhaust->runAction(spa);
}

void Jetpack::update(float dt)
{
	SkillBase::update(dt);

	if (player->keyMap["up"] == true && player->inTheAir && player->isDoubleJump) {
		if (onAction)
			player->MoveDelay(true, false);
		onAction = false;
		player->status->gravitation = anti_gravitation;
		if (player->y_speed > player->status->y_maxSpeed/1.2)
			player->y_speed -= player->status->gravitation * dt;

		Emission();
	}
	else {
		player->status->gravitation = gravitation;
		onAction = true;
	}

	if (jetpack->isFlippedX() != player->isFlippedX()) {
		jetpack->setFlippedX(player->isFlippedX());
		jetpack->setPositionX(-jetpack->getPositionX());
	}
}
