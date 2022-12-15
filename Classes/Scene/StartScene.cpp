#include "StartScene.h" 
#include"Scene/Loading.h"

bool StartScene::init() {
	
	if (!Scene::init())
	{
		return false;
	}

	//背景音乐控制（暂时没有考虑音量问题）
	auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume;
	if (!instance->isBackgroundMusicPlaying()) {
		//volume = 1.0f;
	}
	else {
		//volume = instance->getBackgroundMusicVolume();
		instance->stopBackgroundMusic(); //stop后无法恢复播放
	}
	instance->playBackgroundMusic("Music/Start.mp3", true);
	//instance->setBackgroundMusicVolume(volume);
	//auto backgroundAudioID = AudioEngine::play2d("Music/Start.mp3", true);//如果只这样简单设置的话，会导致每返回一次，就会开始播放背景音乐，导致音乐重叠。



	//设置delay， 否则捕捉不到场景切换
	auto* delay = DelayTime::create(1.05f);
	auto* func = CallFunc::create([this]() {
		Director::getInstance()->replaceScene(Loading::createScene());
		});
	this->runAction(Sequence::create(delay, func, nullptr));

	

}
