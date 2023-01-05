#ifndef PLAYER_SETUP_H
#define PLAYER_SETUP_H

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui/CocosGUI.h"
#include"Manager/UserManager.h"
#include<algorithm>
#include<string>

using namespace cocos2d;
using namespace ui;


class PlayerSetup : public Scene
{
public:
	virtual bool init();
	void buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void buttonCotinue(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	
	void UserID1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void UserID2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	
	void Deco1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECdrop1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECtire1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECblackhat1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECwhitehat1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECangel1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void Deco2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECdrop2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECtire2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECblackhat2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECwhitehat2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void DECangel2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);

	void bodyColor1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);	
	void SQblack1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQblue1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQgreen1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQpink1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQpurple1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQred1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQwhite1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQyellow1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void bodyColor2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQblack2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQblue2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQgreen2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQpink2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQpurple2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQred2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQwhite2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void SQyellow2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);

	void face1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCcross1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCglass1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCnormal1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCsmiledot1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCsmiletiebag1(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void face2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCcross2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCglass2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCnormal2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCsmiledot2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);
	void FCsmiletiebag2(Ref* ref, cocos2d::ui::Widget::TouchEventType type);


	CREATE_FUNC(PlayerSetup);

private:
	void onMouseMove(Event* event);
	Sprite* blacksprite;
	bool move = false;
};

#endif