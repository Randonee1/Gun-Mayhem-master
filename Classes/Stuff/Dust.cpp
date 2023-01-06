#include "Dust.h"

Dust* Dust::create(MapBase* map, Vec2 point)
{
	auto dust = new Dust();
	if (dust && dust->init()) {
		point.y -= 90;
		dust->setPosition(point);
		map->platform->addChild(dust, 3);
		dust->autorelease();
		return dust;
	}
	CC_SAFE_DELETE(dust);
	return nullptr;
}

bool Dust::init()
{
	if (!Sprite::init())
		return false;

	for (int i = 0; i< 5;i++)
		Dusts.push_back(Sprite::create("dust.png"));

	for (auto& dust : Dusts) {
		float x = rand() % 2 - 1 < 0 ? GameManager::Random(0,200) : -(GameManager::Random(0, 200));
		float y = GameManager::Random(-30, 150);
		float time = GameManager::Random(6, 16) / 10.0f;
		auto move = EaseSineOut::create(MoveBy::create(time, Vec2(x, 0)));
		auto move_up = MoveBy::create(time, Vec2(0, y));
		auto shrink = ScaleBy::create(time, 0);
		auto Dissipate = CallFunc::create([&]() {dissipate++; });
		auto spa = Spawn::create(move,move_up, shrink, nullptr);
		auto seq = Sequence::create(spa, Dissipate, nullptr);
		dust->setScale(GameManager::Random(3, 7)/2.0f);
		dust->setOpacity(GameManager::Random(60, 150));
		dust->setPosition(x/3, 0);
		this->addChild(dust);
		dust->runAction(seq);
	}
	return true;
}

void Dust::update(float dt)
{
}
