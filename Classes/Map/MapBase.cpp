#include "MapBase.h"

bool MapBase::init()
{
	if (!Layer::init())
		return false;
	visibleSize = Director::getInstance()->getVisibleSize();
	return true;
}
