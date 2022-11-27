#include "Loading.h"

Scene* Loading::createScene()
{
    auto scene = Scene::create();
    auto layer = Loading::create();
    scene->addChild(layer);
    return scene;
}

bool Loading::init()
{
    if (!Layer::init())
        return false;
    isloaddone = false;
    auto back = LayerColor::create(Color4B::GRAY, 12000, 10000);
    back->setIgnoreAnchorPointForPosition(false);
    back->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(back);
    schedule(CC_SCHEDULE_SELECTOR(Loading::logic));
    return true;
}

void Loading::loadResources()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("test.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("space.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Player1.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MG_gtl.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("body_fx.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("blood.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bodyColored.plist");

    isloaddone = true;
}

void Loading::logic(float dt)
{
    if (!isloaddone) {
        loadResources();
    }
    if (isloaddone) {
        //暂时的写法，后面写完WelcomeScene再换
        auto scene = GameScene::CreateGame(0);
        Director::getInstance()->replaceScene(scene);
    }
}
