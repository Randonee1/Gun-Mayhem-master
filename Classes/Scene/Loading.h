#ifndef LOADING_H
#define LOADING_H

#include "cocos2d.h"
#include "GameScene.h"
#include "Transition.h"

USING_NS_CC;

class Loading : public Layer 
{
public:
	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(Loading);

	void loadResources();
	void logic(float dt);
	bool isloaddone;
};


#endif