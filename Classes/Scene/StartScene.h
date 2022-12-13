#ifndef _STARTSCENE_
#define _STARTSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include"Global.h"

using namespace cocos2d;
using namespace ui;



class StartScene : public Scene
{
public:
	virtual bool init();
	CREATE_FUNC(StartScene);
	
	
};
#endif