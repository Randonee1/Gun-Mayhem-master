#include "BaseBall.h"
#include "Sprite/CharacterBase.h"

bool BaseBall::init(CharacterBase* player, Vec2 init, Vec2 offset)
{
	player->shotCount++;
	this->player = player;
	this->back = player->map->platform;
	bullet = Sprite::create("baseball.png");
	this->setFlippedX(player->isFlippedX());
	bullet->setFlippedX(player->isFlippedX());
	this->x_bulletSpeed = player->x_speed + (player->isFlippedX() ? -player->gun->bulletSpeed : player->gun->bulletSpeed);
	this->y_bulletSpeed = 0;
	this->hitSpeed = player->isFlippedX() ? -player->gun->hitSpeed : player->gun->hitSpeed;
	currentPoint = init + offset;
	this->addChild(bullet, 0);
	this->setPosition(currentPoint);
	back->addChild(this, 0);
	this->scheduleUpdate();
	return true;
}

void BaseBall::update(float dt)
{
	currentPoint.x += x_bulletSpeed * dt;
	y_bulletSpeed -= 1000 * dt;
	currentPoint.y += y_bulletSpeed * dt;
	this->setPosition(currentPoint);
}

BaseBall* BaseBall::create(CharacterBase* player, Vec2 init, Vec2 offset)
{
	auto ball = new BaseBall();
	if (ball && ball->init(player, init, offset)) {
		ball->autorelease();
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return nullptr;
}
