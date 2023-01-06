#ifndef _STANDING_
#define _STANDING_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Transition.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include"Manager/UserManager.h"
#include"Scene/StartScene.h"
#include <math.h> 

using namespace CocosDenshion;
using namespace cocos2d;
using namespace ui;


typedef std::pair<std::string, std::vector<double>> PAIR;
class Standing : public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	std::string twoDec_ToString(double d);

	static bool cmp_by_value(const PAIR& lhs, const PAIR& rhs);

	// a selector callback
	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(Standing);
};
#endif