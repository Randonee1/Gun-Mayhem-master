#ifndef BACKGROUND_CHOISE_H
#define BACKGROUND_CHOISE_H

#include "cocos2d.h"
#include "Transition.h"
#include "extensions\cocos-ext.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;


class BackgroundChoise : public Scene
{
public:
	virtual bool init();
	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void buttonCotinue(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	CREATE_FUNC(BackgroundChoise);

private:
	void onMouseMove(Event* event);
	Sprite* blacksprite;
	EditBox* editbox1;
	bool move = false;
};

#endif 


//
//auto Random = Button::create("customGameMenu/randomUnselected.png", "customGameMenu/randomSelected.png");
//Random->setPosition(Vec2(origin.x + visibleSize.width * 717.5 / 2560, 1440 - 420));
//
//auto spacestation = Button::create("customGameMenu/spacestationUnselected.png", "customGameMenu/spacestationSelected.png");
//spacestation->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 530));
//
//auto sunsetcity = Button::create("customGameMenu/sunsetcityUnselected.png", "customGameMenu/sunsetcitySelected.png");
//sunsetcity->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 610));
//
//auto seele = Button::create("customGameMenu/seeleUnselected.png", "customGameMenu/seeleSelected.png");
//seele->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 690));
//
//auto irismood = Button::create("customGameMenu/irismoodUnselected.png", "customGameMenu/irismoodSelected.png");
//irismood->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 770));
//
//auto highmoon = Button::create("customGameMenu/highmoonUnselected.png", "customGameMenu/highmoonSelected.png");
//highmoon->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 850));
//
//auto Default = Button::create("customGameMenu/defaultUnselected.png", "customGameMenu/defaultSelected.png");
//Default->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 930));