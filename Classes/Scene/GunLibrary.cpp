#include "GunLibrary.h"

Scene* GunLibrary::createScene()
{
    auto scene = Scene::create();

    auto layer = GunLibrary::create();

    scene->addChild(layer);

    return scene;
}

bool GunLibrary::init()
{
    if (!Layer::init()) {
        return false;
    }
    //init
}