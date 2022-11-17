#include "Bullet.h"

bool Bullet::init(Node* back, Vec2 init, bool direction)
{
	if (!Sprite::init()) {
		return false;
	}
	this->back = back;
	bullet = Sprite::createWithSpriteFrameName("razer.png");
	bullet->setFlippedX(direction);
	speed = direction? -2000: 2000;
	currentPoint = init + (direction ? Vec2(-50, 30) : Vec2(50, 30));
	this->addChild(bullet, 0);
	this->setPosition(currentPoint);
	back->addChild(this, 0);
	this->scheduleUpdate();
	return true;
}

void Bullet::update(float dt)
{
	Node::update(dt);
	currentPoint.x += speed * dt;
	this->setPosition(currentPoint);
	Node* player1_Body = back->getChildByTag(1)->getChildByTag(0)->getChildByTag(0);
	//Node* player2_Body = back->getChildByTag(2)->getChildByTag(0)->getChildByTag(0);

	if (this->getPositionX() > 12000 || this->getPositionX() < 0)
		this->removeFromParent();
}

Bullet* Bullet::create(Node* back, Vec2 init, bool direction)
{
	auto bullet = new Bullet();
	if (bullet && bullet->init(back, init, direction)) {
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}
