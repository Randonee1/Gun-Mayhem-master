#include "PackageBase.h"

bool PackageBase::init(MapBase* map)
{
    if (!Sprite::init())
        return false;

    updatetime = 0;
    y_speed = 0;

    unsigned seed = time(0);
    srand(seed);
    int endfloor = rand() % (map->Floor.size());
    endFloor = endfloor * map->floor_height + map->floor_base;

    setPosition(rand() % int(map->platform->getContentSize().width / 2) + map->platform->getContentSize().width / 4,
        map->platform->getContentSize().height + 2000);

    map->platform->addChild(this, 0);

    scheduleUpdate();
    return true;
}

void PackageBase::GetPackage(CharacterBase* player)
{
    return;
}

void PackageBase::update(float dt)
{   
    if (getPositionY() > endFloor) {
        y_speed += dt * gravitation;
        this->setPosition(this->getPositionX(), this->getPositionY() + y_speed * dt);
    }
}