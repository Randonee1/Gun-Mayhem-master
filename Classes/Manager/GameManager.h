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

	static GameManager* _instance;

	static std::map<std::string, EventKeyboard::KeyCode> map1;
	static std::map<std::string, EventKeyboard::KeyCode> map2;

	static std::map<std::string, const char*> Bodys;
	static std::map<std::string, const char*> Faces;
	static std::map<std::string, const char*> Heads;
	static std::map<std::string, const char*> Hands;
	static std::map<std::string, const char*> Feet;

	static std::map<std::string, const char*> Hats;
	static std::map<std::string, const char*> Costumes;

};

#endif

