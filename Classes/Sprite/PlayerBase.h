#ifndef PLAYER_BASE_H
#define PLAYER_BASE_H

#include "cocos2d.h"
#include "Organ/Body.h"
#include "Organ/Face.h"
#include "Organ/Foot.h"
#include "Organ/Hand.h"
#include "Organ/Head.h"
#include "Organ/OrganBase.h"
#include "Weapons/Gun/GunBase.h"

USING_NS_CC;

class PlayerBase : public Sprite
{
public:

	//static Sprite* createSprite();

	//bool init() override;
	//CREATE_FUNC(PlayerBase);

	bool initWithTag(int name);
	static PlayerBase* createWithTag(int name);

	int name;
	std::map<std::string, EventKeyboard::KeyCode> keymap;
	std::vector<OrganBase*> organs;

	Body* body;
	Head* head;
	Face* face;
	Foot* feet1;
	Foot* feet2;
	Hand* hand1;
	Hand* hand2;
	GunBase* gun;

	void update(float dt) override;

protected:
	float floor;
	float x_speed;
	float y_speed;
	float x_maxSpeed;
	float y_maxSpeed;
	float recoil_speed;
	float accelerate;
	float acceleration;
	float gravitation;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	bool isDoubleJump;
	bool inTheAir;

	void initBody();

	float Right();
	float Left();
	void Flip(bool direction);
	
	void initKeyboardListener();

	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	void MoveDelay(bool up,bool floor);
	int lasttag = 1;
};

#endif