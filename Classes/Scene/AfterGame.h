#ifndef _AFTERGAME_
#define _AFTERGAME_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Transition.h"
#include"Manager/UserManager.h"
#include"Scene/StartScene.h"
#include<fstream>

using namespace cocos2d;
using namespace ui;

class AfterGame : public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);

	std::map<std::string, std::vector<double>> calculate(std::string, std::map<std::string, std::vector<double>>&);

	std::string Dec_ToString(double d);
	// implement the "static create()" method manually
	CREATE_FUNC(AfterGame);
};
#endif