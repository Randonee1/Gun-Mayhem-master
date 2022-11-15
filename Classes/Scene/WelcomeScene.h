#ifndef WELCOME_SCENE_H
#define WELCOME_SCENE_H

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public Layer
{
public:
	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(WelcomeScene);

	//生成背景
	void initBackGround();

	//生成Logo
	void initLogo();

	//生成菜单
	void initButton();

	//退出按键
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) override;

private:
};

#endif