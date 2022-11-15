#include "PlayerSetup.h"

Scene* PlayerSetup::createScene()
{
    auto scene = Scene::create();

    auto layer = PlayerSetup::create();

    scene->addChild(layer);

    return scene;
}

bool PlayerSetup::init()
{
    if (!Layer::init()) {
        return false;
    }
    //init
}