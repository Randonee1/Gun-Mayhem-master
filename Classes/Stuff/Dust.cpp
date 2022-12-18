#include "Dust.h"

void Dust::create(MapBase* map, Vec2 point)
{
	auto dust = new Dust();
	if (dust && dust->init()) {
		point.y -= 50;
		dust->setPosition(point);
		map->platform->addChild(dust, 3);
		dust->autorelease();
		return;
	}
	CC_SAFE_DELETE(dust);
	return;
}

bool Dust::init()
{
	if (!Sprite::init())
		return false;
	auto move = EaseSineOut::create(MoveBy::create(1, Vec2(100, 0)));
	auto shrink = ScaleBy::create(1,0);
	auto spa = Spawn::create(move, shrink, nullptr);

	Dusts.push_back(Sprite::create("dust.png"));

	for (auto& dust : Dusts) {
		this->addChild(dust);
		dust->runAction(spa->clone());
	}
	return true;
}

void Dust::update(float dt)
{
}
