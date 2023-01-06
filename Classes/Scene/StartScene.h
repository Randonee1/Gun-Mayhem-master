#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "AudioEngine.h"
#include "Transition.h"
#include "Map/MapBase.h"
#include"Scene/Setting.h"
#include"Scene/BackgroundChoise.h"
#include"Manager/GameManager.h"
#include"Manager/UserManager.h"


#include<fstream>


using namespace cocos2d;
using namespace ui;



class StartScene : public Scene
{
public:
	virtual bool init();

	CREATE_FUNC(StartScene);

	//static StartScene* create();

	void initMusic();

	void initGame();

	void initButton();

	void initFile();

	void onMouseMove(Event* event);

	void onEnterTransitionDidFinish() override;

private:
	MapBase* game;
	Sprite* blacksprite;
	bool move = false;
};
#endif