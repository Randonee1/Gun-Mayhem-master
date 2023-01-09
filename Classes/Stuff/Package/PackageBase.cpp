#include "PackageBase.h"

bool PackageBase::init(MapBase* map)
{
    if (!Sprite::init())
        return false;

    updatetime = 0;
    y_speed = 0;
    this->map = map;

    unsigned seed = time(0);
    srand(seed);
    endFloor = rand() % (map->Floor.size());

    float x = GameManager::Random(int(map->Floor[endFloor].front()), int(map->Floor[endFloor].back()));
    while (!map->InTheBoundary(map->Floor[endFloor], x))
        x = GameManager::Random(int(map->Floor[endFloor].front()), int(map->Floor[endFloor].back()));
    setPosition(x, map->platform->getContentSize().height + 2000);

    map->platform->addChild(this, 0);

    scheduleUpdate();
    return true;
}

void PackageBase::GetPackage(CharacterBase* player)
{
    return;
}

bool PackageBase::Disappear() {
    return (!package->isVisible());
}

void PackageBase::update(float dt)
{   
    duration -= dt;
    if (duration < 0 && duration+dt>=0) {
        auto fade = FadeOut::create(1);
        auto disappear = CallFunc::create([&]() {package->setVisible(false); });
        auto seq = Sequence::create(fade, disappear, nullptr);
        package->runAction(seq->clone());
        if(!package->getChildren().empty())
            package->getChildren().front()->runAction(seq->clone());
    }
    if (getPositionY() > map->floor_base + map->floor_height * endFloor) {
        y_speed += dt * gravitation;
        this->setPosition(this->getPositionX(), this->getPositionY() + y_speed * dt);
    }
    else{
        this->intheair = false;
    }
}