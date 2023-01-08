#include "BulletCase.h"

bool BulletCase::init(Node* back, Vec2 init,Vec2 offset, bool direction,int rand_x, int rand_y)
{
	if (!Sprite::init()) {
		return false;
	}
	bulletcase = Sprite::createWithSpriteFrameName("bulletcase.png");
	bulletcase->setFlippedX(direction);
	
	y_speed = float(rand() % rand_y + rand_y / 2);
	x_speed = float(rand() % rand_x - rand_x / 2);
	direction ? offset.x = -offset.x : offset.x = offset.x;
	currentPoint = init + offset;
	float r = rand() % 360 - 180;
	auto rotate = RepeatForever::create(RotateBy::create(0.3, r));
	bulletcase->runAction(rotate);
	this->addChild(bulletcase, 3);
	this->setPosition(currentPoint);
	back->addChild(this, 100);
	this->scheduleUpdate();
	return true;
}

void BulletCase::update(float dt)
{
	Node::update(dt);
	y_speed += gravitation * dt;
	currentPoint.x += x_speed * dt;
	currentPoint.y += y_speed * dt;
	this->setPosition(currentPoint);
	if (this->getPositionY() < 0)
		this->removeFromParent();
}

BulletCase* BulletCase::create(Node* back, Vec2 init, Vec2 offset, bool direction, int rand_x, int rand_y)
{
	auto bulletcase = new BulletCase();
	if (bulletcase && bulletcase->init(back, init, offset, direction,rand_x, rand_y)) {
		bulletcase->autorelease();
		return bulletcase;
	}
	CC_SAFE_DELETE(bulletcase);
	return nullptr;
}
