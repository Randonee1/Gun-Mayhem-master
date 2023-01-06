#include "Bullet.h"
#include "Sprite/CharacterBase.h"

bool Bullet::init(CharacterBase* player, Vec2 init, Vec2 offset)
{
	if (!Sprite::init()) {
		return false;
	}
	player->shotCount++;
	this->player = player;
	this->back = player->map->platform;
	bullet = Sprite::createWithSpriteFrameName("razer.png");
	this->setFlippedX(player->isFlippedX());
	bullet->setFlippedX(player->isFlippedX());
	this->bulletSpeed = player->isFlippedX() ? -player->gun->bulletSpeed: player->gun->bulletSpeed;
	this->hitSpeed = player->isFlippedX() ? -player->gun->hitSpeed : player->gun->hitSpeed;
	player->isFlippedX() ? offset.x = -offset.x : offset.x = offset.x;
	currentPoint = init + offset;
	this->addChild(bullet, 0);
	this->setPosition(currentPoint);
	back->addChild(this, 0);
	this->scheduleUpdate();
	return true;
}

void Bullet::update(float dt)
{
	Node::update(dt);
	currentPoint.x += bulletSpeed * dt;
	this->setPosition(currentPoint);
	
}

Bullet* Bullet::create(CharacterBase* player, Vec2 init, Vec2 offset)
{
	auto bullet = new Bullet();
	if (bullet && bullet->init(player, init, offset)) {
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}
