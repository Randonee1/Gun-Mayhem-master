#ifndef PACKAGE_BASE_H
#define PACKAGE_BASE_H

#include "cocos2d.h"
USING_NS_CC;

class PackageBase : public Sprite
{
public:

	bool init() override;



	CREATE_FUNC(PackageBase);
};

#endif