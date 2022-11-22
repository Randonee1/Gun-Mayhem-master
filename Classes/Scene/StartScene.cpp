#include "StartScene.h" 
#include"Scene/Loading.h"

bool StartScene::init() {
	
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	

	//设置背景图片
	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(Vec2(origin.x, origin.y));
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//添加游戏标题
	auto label = Label::createWithTTF("Gun Mayhem", "fonts/Marker Felt.ttf", 196);
	label->setTextColor(Color4B::GRAY);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(origin.x + visibleSize.width / 20, origin.y + visibleSize.height * 19 / 20);
	label->setScaleX(1.3f);
	label->enableShadow();
	this->addChild(label);


	//设置菜单项
	//文字菜单项
	MenuItemFont* GameMenu = MenuItemFont::create("Game Begin", [&](Ref* sender) {
		Director::getInstance()->replaceScene(Loading::createScene());
		});
	GameMenu->setColor(Color3B::WHITE);
	GameMenu->setFontNameObj("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF");
	//GameMenu->setFontSize(200);
	GameMenu->setFontSizeObj(100);
	
	MenuItemFont* SettingMenu = MenuItemFont::create("Setting", [&](Ref* sender) {
		//Director::getInstance()->replaceScene(setting::createScene());
		});
	SettingMenu->setColor(Color3B::WHITE);
	SettingMenu->setFontNameObj("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF");
	SettingMenu->setFontSizeObj(100);
	SettingMenu->setPosition(0, -200);


	MenuItemFont* WeaponMenu = MenuItemFont::create("Weapon", [&](Ref* sender) {
		//Director::getInstance()->replaceScene(setting::createScene());
		});
	WeaponMenu->setColor(Color3B::WHITE);
	WeaponMenu->setFontNameObj("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF");
	WeaponMenu->setFontSizeObj(100);
	WeaponMenu->setPosition(0, -400);



	//创建菜单
	auto menu = Menu::create(GameMenu, SettingMenu,WeaponMenu,NULL);
	menu->setPosition(Vec2(origin.x + visibleSize.width * 6/ 7,origin.y + visibleSize.height * 3/5));
	this->addChild(menu,1);


	//鼠标监听器//GameBegin的监听
	blacksprite = Sprite::create("BlacktTransparent.png");
	blacksprite->setAnchorPoint(Point(0, 0.5));
	this->addChild(blacksprite);
	blacksprite->setVisible(false);

	auto _mouseListener = EventListenerMouse::create();

	_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
	
	//Setting 监听
	//auto _mouseListenerSt = EventListenerMouse::create();

	//_mouseListenerSt->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove_Setting, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListenerSt, this);

	////Weapon监听
	//auto _mouseListenerWp = EventListenerMouse::create();

	//_mouseListenerWp->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove_Weapon, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListenerWp, this);



}


void StartScene::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));


	Rect r1 = Rect(0, visibleSize.height * 3 / 5 -50, visibleSize.width * 6 / 7, 200);
	Rect r2 = Rect(0, visibleSize.height * 3 / 5 - 250, visibleSize.width * 6 / 7, 200);
	Rect r3 = Rect(0, visibleSize.height * 3 / 5 - 450, visibleSize.width * 6 / 7, 200);
	CallFunc* setMove = CallFunc::create([&]() {
		move = !move;
		});

	if (r1.containsPoint(locationInNode)) {
		if(blacksprite->isVisible()){
			if(!move){
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 3 / 5)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5));
			blacksprite->setVisible(true);
			auto fadein = FadeIn::create(0.1);
			blacksprite->runAction(fadein);
		}
	}
	else if (r2.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if(!move){
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 3 / 5 - 200)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5 - 200));
			blacksprite->setVisible(true);
			auto fadein = FadeIn::create(0.1);
			blacksprite->runAction(fadein);
		}
	}
	else if (r3.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if(!move){
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 3 / 5 - 400)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5 - 400));
			blacksprite->setVisible(true);
			auto fadein = FadeIn::create(0.1);
			blacksprite->runAction(fadein);
		}
	}
	else {
		if(blacksprite->isVisible()){
			CallFunc* func1 = CallFunc::create([&]() {
				blacksprite->setVisible(false);
				});
			auto fadeout = FadeOut::create(0.1f);
			auto seq = Sequence::create(fadeout, func1, nullptr);
			blacksprite->runAction(seq);
		}
	}
}

//void StartScene::onMouseMove_Setting(Event* event)
//{
//	EventMouse* e = (EventMouse*)event;
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
//
//	Rect r = Rect(0, visibleSize.height * 3 / 5 - 250, visibleSize.width * 6 / 7, 100);
//	auto blacksprite = Sprite::create("BlacktTransparent.png");
//	blacksprite->setAnchorPoint(Point(0, 0.5));
//	blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5 -200));
//
//	r.containsPoint(locationInNode) ? selected(blacksprite) : unselected(blacksprite);
//}
//
//void StartScene::onMouseMove_Weapon(Event* event)
//{
//	EventMouse* e = (EventMouse*)event;
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
//
//	Rect r = Rect(0, visibleSize.height * 3 / 5 - 450, visibleSize.width * 6 / 7, 100);
//	auto blacksprite = Sprite::create("BlacktTransparent.png");
//	blacksprite->setAnchorPoint(Point(0, 0.5));
//	blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5 - 400));
//
//	r.containsPoint(locationInNode) ? selected(blacksprite) : unselected(blacksprite);
//}


void StartScene::selected(Sprite* s)
{
	log("Mouse Move");
	this->addChild(s);
	FadeOut* fadeOut = FadeOut::create(0.5f);
	s->runAction(fadeOut);

}
void StartScene::unselected(Sprite *s) {

}

//void StartScene::update(float dt)
//{
//	
//}

























//
//MenuItemFont* StartScene::menuCreate(const std::string& titleText, pFunc switchSceneEvent)const {
//	MenuItemFont* p = new MenuItemFont;
//	if (p == nullptr)
//	{
//		return nullptr;
//	}
//	p = MenuItemFont::create(titleText);
//	p->setColor(Color3B::WHITE);
//	p->setFontName("fonts/arial.ttf");
//	p->setFontSize(48);
//	Widget::addTouchEventListener(switchSceneEvent);
//}


//Button* StartScene::buttonCreate(const std::string& titleText, pFunc switchSceneEvent)const
//{
//	Button* p = new(std::nothrow) Button;
//	if (p == nullptr)
//	{
//		return nullptr;
//	}
//	p = Button::create("choice.png", "unchoice.png");
//	p->setTitleText(titleText);
//	p->setTitleColor(Color3B::WHITE);
//	p->setTitleFontName("fonts/Marker Felt.ttf");
//	p->setTitleFontSize(48);
//	p->addTouchEventListener(switchSceneEvent);
//	return p;
//}
//
//
//
//void StartScene::buttonAdd(const std::vector<Button*>& buttonList)
//{
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	auto origin = Director::getInstance()->getVisibleOrigin();
//	for (auto iterator = buttonList.begin(); iterator < buttonList.end(); iterator++)
//	{
//		(*iterator)->setPosition(Vec2(origin.x + visibleSize.width * 4 / 5,
//			origin.y + visibleSize.height * 3 / 5 - (iterator - buttonList.begin()) * 1.7f * (*iterator)->getContentSize().height));
//		this->addChild(*iterator);
//	}
//
//}