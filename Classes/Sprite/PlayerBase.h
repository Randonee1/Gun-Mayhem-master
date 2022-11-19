#ifndef PLAYER_BASE_H
#define PLAYER_BASE_H

#include "cocos2d.h"
#include "CharacterBase.h"
#include "Manager/GameManager.h"

USING_NS_CC;



class PlayerBase : public CharacterBase
{
public:

	//static PlayerBase* createWithTag(int name,Sprite* background);

	bool initWithTag(int name, MapBase* map);

	virtual void initBody();

	void initKeyboardListener();
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	void update(float dt) override;

protected:

	int name;
	std::map<std::string, EventKeyboard::KeyCode> keymap;
	
};

#endif