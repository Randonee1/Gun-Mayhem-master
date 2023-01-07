#ifndef GUN_LIBRARY_H
#define GUN_LIBRARY_H

#include "cocos2d.h"
#include "Transition.h"
#include"Scene/StartScene.h"
USING_NS_CC;

class GunLibrary : public Scene
{
public:

	static Scene* createScene();

	bool init() override;

	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);

	CREATE_FUNC(GunLibrary);
};

#endif