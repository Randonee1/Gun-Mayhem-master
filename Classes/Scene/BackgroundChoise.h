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
