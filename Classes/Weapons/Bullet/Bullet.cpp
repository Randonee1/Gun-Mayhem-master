#include "Bullet.h"

bool Bullet::init(Node* back, Vec2 init, Vec2 offset, float speed, bool direction)
{
	if (!Sprite::init()) {
		return false;
	}
	this->back = back;
	bullet = Sprite::createWithSpriteFrameName("razer.png");
	this->setFlippedX(direction);
	bullet->setFlippedX(direction);
	this->speed = direction? -speed: speed;
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
	currentPoint.x += speed * dt;
	this->setPosition(currentPoint);
	/*Node* player1_Body = back->getChildByTag(1)->getChildByTag(0)->getChildByTag(0);
	Node* player2_Body = back->getChildByTag(2)->getChildByTag(0)->getChildByTag(0);

	auto rect1 = player1_Body->getBoundingBox();
	Vec2 offset1 = back->getChildByTag(1)->getPosition() + back->getChildByTag(1)->getChildByTag(0)->getPosition();
	rect1.origin += offset1;

	auto rect2 = player2_Body->getBoundingBox();
	Vec2 offset2 = back->getChildByTag(2)->getPosition() + back->getChildByTag(2)->getChildByTag(0)->getPosition();
	rect2.origin += offset2;

	if (rect1.containsPoint(this->getPosition()))
	{
		remove = true;
	}

	if (rect2.containsPoint(this->getPosition()))
	{
		remove = true;
	}

	if (this->getPositionX() > 12000 || this->getPositionX() < -6000)
		remove = true;
	if (remove)
		this->removeFromParent();*/
}

Bullet* Bullet::create(Node* back, Vec2 init, Vec2 offset, float speed, bool direction)
{
	auto bullet = new Bullet();
	if (bullet && bullet->init(back, init, offset, speed, direction)) {
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}
