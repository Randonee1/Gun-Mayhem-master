#ifndef LOADING_H
#define LOADING_H

#include "cocos2d.h"
USING_NS_CC;

class Loading : public Layer 
{
	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(Loading);

	void loadSouce();
	void logic(float dt);
};


#endif