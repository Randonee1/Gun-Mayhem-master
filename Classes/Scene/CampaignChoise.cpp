#include "CampaignChoise.h"

Scene* CampaignChoise::createScene()
{
    auto scene = Scene::create();

    auto layer = CampaignChoise::create();

    scene->addChild(layer);

    return scene;
}

bool CampaignChoise::init()
{
    if (!Layer::init()) {
        return false;
    }
    //init
}
