#include"Scene/Credits.h"
#include"Scene/StartScene.h"

Scene* Credits::createScene()
{
	return Credits::create();
}
bool Credits::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//´´½¨±³¾°
	auto background = Sprite::create("staff/background.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);;
	this->addChild(background);

	//back°´Å¥
	auto BackToMenuButton = ui::Button::create("staff/back.png", "staff/back.png");
	BackToMenuButton->setScale(1.0f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(Credits::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * 2222 / 2560, origin.y + 1440 - 1292));
	this->addChild(BackToMenuButton);

}

void Credits::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(Transition::create(0.5f, StartScene::create()));
		break;
	default:
		break;
	}


}