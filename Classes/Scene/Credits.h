#ifndef _CREDITS_
#define _CREDITS_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Transition.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;
using namespace ui;

class Credits : public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(Credits);
};
#endif