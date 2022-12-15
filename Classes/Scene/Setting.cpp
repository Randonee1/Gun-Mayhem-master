#include "Setting.h"



#include "Setting.h" 
#include"StartScene.h"

Scene* Setting::createScene()
{
	return Setting::create();
}
bool Setting::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//log(visibleSize);
	//创建背景
	auto background = Sprite::create("optionMenu/back.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);;
	this->addChild(background);
	//back按钮
	auto BackToMenuButton = ui::Button::create( "optionMenu/backtoUnselected.png", "optionMenu/backtoSelected.png");
	BackToMenuButton->setScale(1.0f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(Setting::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * 2085/2560, origin.y +1440-1175));
	this->addChild(BackToMenuButton);



	//设置背景音乐按钮
	auto onMusic = Button::create("optionMenu/onSelected.png", "optionMenu/onUnselected.png");
	onMusic->setPosition(Vec2(origin.x + visibleSize.width * 1935/2560, 1440 - 585));
	
	auto offMusic = Button::create("optionMenu/offUnselected.png", "optionMenu/offSelected.png");
	offMusic->setPosition(Vec2(origin.x + visibleSize.width * 2235/2560, 1440 - 585));


	//设置背景音乐按钮的回调函数
	onMusic->addClickEventListener([=](Ref* sender) {                      
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);
		onMusic->loadTextureNormal("optionMenu/onSelected.png");
		offMusic->loadTextureNormal("optionMenu/offUnselected.png");
		});
	
	offMusic->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
		onMusic->loadTextureNormal("optionMenu/onUnselected.png");
		offMusic->loadTextureNormal("optionMenu/offSelected.png");
		});

	this->addChild(onMusic);
	this->addChild(offMusic);



	//设置音效按钮
	auto onSound = Button::create("optionMenu/onSelected.png", "optionMenu/onUnselected.png");
	onSound->setPosition(Vec2(origin.x + visibleSize.width * 1935 / 2560, 1440 - 890));
	
	auto offSound = Button::create("optionMenu/offUnselected.png", "optionMenu/offSelected.png");
	offSound->setPosition(Vec2(origin.x + visibleSize.width * 2235 / 2560, 1440 - 890));
	

	//设置音效的回调函数
	onSound->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		SimpleAudioEngine::getInstance()->setEffectsVolume(0);
		onSound->loadTextureNormal("optionMenu/onSelected.png");
		offSound->loadTextureNormal("optionMenu/offUnselected.png");
		});

	offSound->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		SimpleAudioEngine::getInstance()->setEffectsVolume(1);
		onSound->loadTextureNormal("optionMenu/onUnselected.png");
		offSound->loadTextureNormal("optionMenu/offSelected.png");
		});

	this->addChild(onSound);
	this->addChild(offSound);


	

}


void Setting::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(StartScene::create());
		break;
	default:
		break;
	}


}
