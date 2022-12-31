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
		float x = rand() % 2 - 1 < 0 ? GameManager::Random(20,70) : -(GameManager::Random(20, 70));
		float y = rand() % 2 - 1 < 0 ? GameManager::Random(10, 20) : -(GameManager::Random(10, 20));
		auto move = EaseSineOut::create(MoveBy::create(1, Vec2(x, y)));
		auto shrink = ScaleBy::create(1, 0);
		auto Dissipate = CallFunc::create([&]() {dissipate = true; });
		auto spa = Spawn::create(move, shrink, nullptr);
		auto seq = Sequence::create(spa, Dissipate, nullptr);
		dust->setScale(GameManager::Random(3, 6)/2.0f);
		dust->setOpacity(GameManager::Random(100, 200));
		dust->setPosition(x, 0);
		this->addChild(dust);
		dust->runAction(seq);
	}
	return true;
}

void Dust::update(float dt)
{
}
