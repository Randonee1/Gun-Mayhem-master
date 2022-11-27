#include "Blood.h"

Blood* Blood::create()
{
	auto blood = new Blood();
	if (blood && blood->init()) {
		blood->autorelease();
		return blood;
	}
	CC_SAFE_DELETE(blood);
	return nullptr;
}

bool Blood::init()
{
	if (!Sprite::init())
		return false;

	BloodSpurtingOut1 = Sprite::createWithSpriteFrameName("BloodSpurtingOut.png");
	this->addChild(BloodSpurtingOut1, 1);
	BloodSpurtingOut2 = Sprite::createWithSpriteFrameName("BloodSpurtingOut.png");
	this->addChild(BloodSpurtingOut2, 2);
	bloodDrop1 = Sprite::createWithSpriteFrameName("bloodDrop1.png");
	this->addChild(bloodDrop1);
	bloodDrop2 = Sprite::createWithSpriteFrameName("bloodDrop2.png");
	this->addChild(bloodDrop2);
	bloodDrop3 = Sprite::createWithSpriteFrameName("bloodDrop3.png");
	this->addChild(bloodDrop3);

	
	auto scale1 = Sequence::create(ScaleTo::create(0, 0.2), ScaleBy::create(0.08, 10), nullptr);
	auto fadeout1 = FadeOut::create(0.08);
	auto spa1 = Spawn::create(scale1, fadeout1, nullptr);
	BloodSpurtingOut1->runAction(spa1);

	auto scale2 = Sequence::create(ScaleTo::create(0, 0.1), ScaleBy::create(0.08, 5), nullptr);
	auto fadeout2 = FadeOut::create(0.08);
	auto spa2 = Spawn::create(scale2, fadeout2, nullptr);
	BloodSpurtingOut2->runAction(spa2);

	unsigned seed = time(0);
	x_speed1 = rand() % 2 - 1 < 0 ? rand() % 500 + 1000 : -(rand() % 500 + 1000);
	x_speed2 = rand() % 2 - 1 < 0 ? rand() % 500 + 1000 : -(rand() % 500 + 1000);
	x_speed3 = rand() % 2 - 1 < 0 ? rand() % 500 + 1000 : -(rand() % 500 + 1000);

	y_speed1 = rand() % 500 + 750;
	y_speed2 = rand() % 500 + 750;
	y_speed3 = rand() % 500 + 750;

	bloodDrop1->setRotation(-Angle(x_speed1, y_speed1));
	bloodDrop2->setRotation(-Angle(x_speed2, y_speed2));
	bloodDrop3->setRotation(-Angle(x_speed3, y_speed3));

	this->scheduleUpdate();

	return true;
}

void Blood::update(float dt)
{
	y_speed1 += dt * gravitation;
	y_speed2 += dt * gravitation;
	y_speed3 += dt * gravitation;

	bloodDrop1->setPosition(bloodDrop1->getPosition() + Vec2(x_speed1 * dt, y_speed1 * dt));
	bloodDrop2->setPosition(bloodDrop2->getPosition() + Vec2(x_speed2 * dt, y_speed2 * dt));
	bloodDrop3->setPosition(bloodDrop3->getPosition() + Vec2(x_speed3 * dt, y_speed3 * dt));

	bloodDrop1->setRotation(-Angle(x_speed1, y_speed1));
	bloodDrop2->setRotation(-Angle(x_speed2, y_speed2));
	bloodDrop3->setRotation(-Angle(x_speed3, y_speed3));

	if (bloodDrop1->getPosition().y < -2000)
		this->removeFromParent();
}

float Blood::Angle(float v_x, float v_y)
{
	return std::atan2(v_y, v_x)/3.14 * 180;
}
