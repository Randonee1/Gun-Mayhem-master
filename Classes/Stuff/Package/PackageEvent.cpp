#include "PackageEvent.h"

PackageEvent* PackageEvent::create(MapBase* map)
{
    auto packageevent = new PackageEvent();
    if (packageevent && packageevent->init(map))
        return packageevent;

    return nullptr;
}

bool PackageEvent::init(MapBase* map)
{
	this->map = map;

	gunUpdateTime = 0;
	skillUpdateTime = 0;

    return true;
}

void PackageEvent::PackageUpdate(std::vector<CharacterBase*>& players)
{

	std::vector<PackageBase* > temp;
	for (auto package : packages) {
		if (package)
			temp.push_back(package);
	}
	packages = temp;

	for (auto& package : packages) {

		if (package->getPositionY() < map->death_line || package->Disappear()) {
			package->removeFromParent();
			package = nullptr;
			continue;
		}
		for (auto& player : players) {
			auto rect = player->body->organ->getBoundingBox();
			Vec2 offset = player->getPosition() + player->body->getPosition();
			rect.origin += offset;

			if (rect.containsPoint(package->getPosition()) && player->valid) {

				package->GetPackage(player);

				package->removeFromParent();
				package = nullptr;

				//添加一个消失动画

				break;
			}
		}

	}

	std::vector<PackageBase* > temp2;
	for (auto package : packages) {
		if (package)
			temp2.push_back(package);
	}
	packages = temp2;
}

void PackageEvent::update(float dt)
{

	if (gunUpdateTime > GunPackage::updatetime) {
		gunUpdateTime = 0;

		auto package_gun_1 = GunPackage::createWithGun(map);
		packages.push_back(package_gun_1);

	}else
		gunUpdateTime += dt;

	if (skillUpdateTime > SkillPackage::updatetime) {
		skillUpdateTime = 0;

		auto package_gun_1 = SkillPackage::createWithSkill(map);
		packages.push_back(package_gun_1);

	}
	else
		skillUpdateTime += dt;
}
