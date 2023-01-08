#include "GunLibrary.h"

Scene* GunLibrary::createScene()
{
    return GunLibrary::create();
}
bool GunLibrary::init()
{
    if (!Scene::init()) {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//´´½¨±³¾°
	auto background = Sprite::create("GunLibrary/background.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	auto baseball_bat=Sprite::create("baseball_bat.png"); //baseball_bat(°ôÇò°ô)
	auto revolver=Sprite::create("revolver.png"); //revolver£¨×óÂÖ£©
	auto Sniper_Rifle=Sprite::create("Sniper_Rifle.png"); //Sniper_Rifle£¨¾Ñ»÷Ç¹£©
	auto uzi=Sprite::createWithSpriteFrameName("MG_Uzi.png"); //uzi
	auto p90=Sprite::createWithSpriteFrameName("MG_P90.png"); //p90
	auto mp7=Sprite::createWithSpriteFrameName("MG_MP7.png"); //mp7
	auto mp5=Sprite::createWithSpriteFrameName("MG_MP5.png");// mp5
	auto d=Sprite::create("gun_test.png"); //double(¿ËÂå¿ËË«Ç¹)
	auto gatling=Sprite::createWithSpriteFrameName("Gatling.png"); //gatling£¨¼ÓÌØÁÖ£©

	auto black = ui::Button::create("gun_board.png", "gun_board.png");

	int x = 580;
	int y = 247.5;
	baseball_bat->setPosition(Vec2(origin.x + visibleSize.width * (410) / 2560, origin.y + 1440-454));
	baseball_bat->setScale(2.0f);
	this->addChild(baseball_bat);
	revolver->setPosition(Vec2(origin.x + visibleSize.width * (410+x) / 2560, origin.y + 1440 - 454));
	revolver->setScale(2.0f);
	this->addChild(revolver);
	Sniper_Rifle->setPosition(Vec2(origin.x + visibleSize.width * (410 + 2*x) / 2560, origin.y + 1440 - 454));
	Sniper_Rifle->setScale(2.0f);
	this->addChild(Sniper_Rifle);
	uzi->setPosition(Vec2(origin.x + visibleSize.width * (410 + 3*x-20) / 2560, origin.y + 1440 - 454+10));
	uzi->setScale(1.8f);
	this->addChild(uzi);
	p90->setPosition(Vec2(origin.x + visibleSize.width * (410-70-7) / 2560, origin.y + 1440 - 454-y-5));
	p90->setScale(2.0f);
	this->addChild(p90);
	mp7->setPosition(Vec2(origin.x + visibleSize.width * (410 + x) / 2560, origin.y + 1440 - 454-y));
	mp7->setScale(2.0f);
	this->addChild(mp7);
	mp5->setPosition(Vec2(origin.x + visibleSize.width * (410 + 2 * x-30) / 2560, origin.y + 1440 - 454-5-y));
	mp5->setScale(2.0f);
	this->addChild(mp5);
	d->setPosition(Vec2(origin.x + visibleSize.width * (410 + 3 * x) / 2560, origin.y + 1440 - 454-y));
	d->setScale(2.2f);
	this->addChild(d);
	gatling->setPosition(Vec2(origin.x + visibleSize.width * (410-130-15) / 2560, origin.y + 1440 - 454 - 2*y+35));
	gatling->setScale(1.5f);
	this->addChild(gatling);

	//back°´Å¥
	auto BackToMenuButton = ui::Button::create("optionMenu/backtoUnselected.png", "optionMenu/backtoSelected.png");
	BackToMenuButton->setScale(0.83f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(GunLibrary::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * (410 + 3 * x) / 2560, origin.y + 1440 - 454-3*y));
	this->addChild(BackToMenuButton);

	return true;
}

void GunLibrary::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(Transition::create(0.5f, StartScene::create()));
		break;
	default:
		break;
	}
}