#include "StartScene.h" 
#include"Scene/Loading.h"

bool StartScene::init() {
	
	if (!Scene::init())
	{
		return false;
	}
	//设置delay， 否则捕捉不到场景切换
	auto* delay = DelayTime::create(1.05f);
	auto* func = CallFunc::create([this]() {
		Director::getInstance()->replaceScene(Loading::createScene());
		});
	this->runAction(Sequence::create(delay, func, nullptr));

}
