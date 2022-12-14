#include "BaseBall.h"

bool BaseBall::init(Node* back, Vec2 init, Vec2 offset, float bulletSpeed, float hitSpeed, bool direction)
{
	this->back = back;
	bullet = Sprite::create("baseball.png");
	this->setFlippedX(direction);
	bullet->setFlippedX(direction);
	this->x_bulletSpeed = direction ? -bulletSpeed : bulletSpeed;
	this->y_bulletSpeed = 0;
	this->hitSpeed = direction ? -hitSpeed : hitSpeed;
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

BaseBall* BaseBall::create(Node* back, Vec2 init, Vec2 offset, float bulletSpeed, float hitSpeed, bool direction)
{
	auto ball = new BaseBall();
	if (ball && ball->init(back, init, offset, bulletSpeed, hitSpeed, direction)) {
		ball->autorelease();
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return nullptr;
}
