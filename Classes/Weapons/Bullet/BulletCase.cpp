#include "BulletCase.h"

bool BulletCase::init(Node* back, Vec2 init, bool direction)
{
	if (!Sprite::init()) {
		return false;
	}
	bulletcase = Sprite::create("bulletcase.png");
	bulletcase->setFlippedX(direction);
	unsigned seed = time(0);
	y_speed = rand()%500+750;
	x_speed = rand()%400-200;
	currentPoint = init + (direction ? Vec2(-20, 60) : Vec2(20, 60));
	float r = rand() % 360 - 180;
	auto rotate = RepeatForever::create(RotateBy::create(0.3, r));
	bulletcase->runAction(rotate);
	this->addChild(bulletcase, 0);
	this->setPosition(currentPoint);
	back->addChild(this, 5);
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
	if (this->getPositionY() < 4500)
		this->removeFromParent();
}

BulletCase* BulletCase::create(Node* back, Vec2 init, bool direction)
{
	auto bulletcase = new BulletCase();
	if (bulletcase && bulletcase->init(back, init,direction)) {
		bulletcase->autorelease();
		return bulletcase;
	}
	CC_SAFE_DELETE(bulletcase);
	return nullptr;
}
