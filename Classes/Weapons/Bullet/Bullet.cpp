#include "Bullet.h"

bool Bullet::init(Node* back, Vec2 init, Vec2 offset, float bulletSpeed,float hitSpeed, bool direction)
{
	if (!Sprite::init()) {
		return false;
	}
	this->back = back;
	bullet = Sprite::createWithSpriteFrameName("razer.png");
	this->setFlippedX(direction);
	bullet->setFlippedX(direction);
	this->bulletSpeed = direction? -bulletSpeed: bulletSpeed;
	this->hitSpeed = direction ? -hitSpeed : hitSpeed;
	direction ? offset.x = -offset.x : offset.x = offset.x;
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
	bool remove = false;
	currentPoint.x += bulletSpeed * dt;
	this->setPosition(currentPoint);
	
}

Bullet* Bullet::create(Node* back, Vec2 init, Vec2 offset, float bulletSpeed,float hitSpeed, bool direction)
{
	auto bullet = new Bullet();
	if (bullet && bullet->init(back, init, offset, bulletSpeed,hitSpeed, direction)) {
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}
