#ifndef SETTING_H
#define SETTING_H

#include "cocos2d.h"
USING_NS_CC;

class Setting : public Layer 
{
public:
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(Setting);
};

#endif 