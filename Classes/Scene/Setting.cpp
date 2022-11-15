#include "Setting.h"

Scene* Setting::createScene()
{
    auto scene = Scene::create();

    auto layer = Setting::create();

    scene->addChild(layer);

    return scene;
}

bool Setting::init()
{
    if (!Layer::init()) {
        return false;
    }
    //init
}