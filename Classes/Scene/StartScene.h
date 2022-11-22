#ifndef _STARTSCENE_
#define _STARTSCENE_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include"Global.h"

using namespace cocos2d;
using namespace ui;
typedef void (*pFunc)(Ref*, Widget::TouchEventType);


class StartScene : public Scene
{
private:	
	void onMouseMove(Event* event);
	/*void onMouseMove_Setting(Event* event);
	void onMouseMove_Weapon(Event* event);*/

	void selected(Sprite *sprite);
	void unselected(Sprite *s);

	//void update(float dt) override;

	Sprite* blacksprite;
	bool move = false;
public:
	virtual bool init();
	CREATE_FUNC(StartScene);
	
	
};
#endif