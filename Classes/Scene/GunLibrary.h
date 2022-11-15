#ifndef GUN_LIBRARY_H
#define GUN_LIBRARY_H

#include "cocos2d.h"
USING_NS_CC;

class GunLibrary : public Layer
{
public:

	static Scene* createScene();

	bool init() override;

	CREATE_FUNC(GunLibrary);
};

#endif