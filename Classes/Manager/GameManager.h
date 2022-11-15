/****************************************************************************
* 
* 
****************************************************************************/

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "cocos2d.h"
USING_NS_CC;

class GameManager
{
public:
	static GameManager* getInstance();

	static std::map<std::string, EventKeyboard::KeyCode> getKeyMap(int name);
private:
	static GameManager* _instance;

	static std::map<std::string, EventKeyboard::KeyCode> map1;
	static std::map<std::string, EventKeyboard::KeyCode> map2;

};

#endif

