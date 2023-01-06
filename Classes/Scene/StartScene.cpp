#include "StartScene.h" 
#include"Scene/Loading.h"
#include"Manager/GameManager.h"
#include "Map/MapTest.h"
#include "Map/MapSpace.h"
#include "Map/MapSunset.h"
#include "Map/MapSeele.h"

bool StartScene::init() {
	
	if (!Scene::init())
	{
		return false;
	}
	initGame();

	initButton();

	return true;
}

void StartScene::initMusic()
{
	//背景音乐控制（暂时没有考虑音量问题）
	auto instance = CocosDenshion::SimpleAudioEngine::getInstance();
	float volume;
	if (!instance->isBackgroundMusicPlaying()) {
		volume = 1.0f;
	}
	else {
		volume = instance->getBackgroundMusicVolume();
		instance->stopBackgroundMusic(); //stop后无法恢复播放
	}
	instance->playBackgroundMusic("Music/Start.mp3", true);
	instance->setBackgroundMusicVolume(volume);
	//auto backgroundAudioID = AudioEngine::play2d("Music/Start.mp3", true);
	//如果只这样简单设置的话，会导致每返回一次，就会开始播放背景音乐，导致音乐重叠。
}

void StartScene::initGame()
{
	auto manager = UserManager::getInstance();

	manager->player_type[1] = false;
	manager->player_type[2] = false;

	manager->player_face[1] = manager->FaceRandom();
	manager->player_face[2] = manager->FaceRandom();

	manager->player_hat[1] = manager->HatRandom();
	manager->player_hat[2] = manager->HatRandom();

	manager->player_skin[1] = manager->SkinRandom();
	manager->player_skin[2] = manager->SkinRandom();

	manager->Live = 10000;

	switch (rand() % 4)
	{
	case(0):
		game = MapTest::createGame();
		break;
	case(1):
		game = MapSpace::createGame();
		break;
	case(2):
		game = MapSunset::createGame();
		break;
	case(3):
		game = MapSeele::createGame();
		break;
	}
	
	this->addChild(game,-1);

	manager->player_type[1] = true;
	manager->player_type[2] = true;

	manager->player_face[1] = "Normal";
	manager->player_face[2] = "Normal";

	manager->player_hat[1] = "None";
	manager->player_hat[2] = "None";

	manager->player_skin[1] = "White";
	manager->player_skin[2] = "White";
}

void StartScene::initButton()
{
	//---------------------------------------------------------------------------------------------------------------------------------------------

	//对主页面添加上一层的文字以及效果

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	//添加游戏标题
	auto label = Label::createWithTTF("Gun Mayhem", "fonts/Marker Felt.ttf", 196);
	label->setTextColor(Color4B::WHITE);
	label->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	label->setPosition(origin.x + visibleSize.width / 20, origin.y + visibleSize.height * 19 / 20);
	label->setScaleX(1.3f);
	label->enableShadow();
	this->addChild(label, 8);


	//设置菜单项
	//文字菜单项
	MenuItemFont* GameMenu = MenuItemFont::create("Game Begin", [&](Ref* sender) {
		auto scene = BackgroundChoise::create();
		//auto scene = GameScene::CreateGame(1);
		Director::getInstance()->replaceScene(Transition::create(0.5f,scene));
		//Director::getInstance()->replaceScene(Loading::createScene());

		});
	GameMenu->setColor(Color3B::WHITE);
	GameMenu->setFontNameObj("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF");
	//GameMenu->setFontSize(200);
	GameMenu->setFontSizeObj(100);

	MenuItemFont* SettingMenu = MenuItemFont::create("Setting", [&](Ref* sender) {
		Director::getInstance()->replaceScene(Transition::create(0.5f, Setting::createScene()));
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
	auto menu = Menu::create(GameMenu, SettingMenu, WeaponMenu, NULL);
	menu->setPosition(Vec2(origin.x + visibleSize.width * 6 / 7, origin.y + visibleSize.height * 3 / 5));
	this->addChild(menu, 8);


	//鼠标监听器//GameBegin的监听
	blacksprite = Sprite::create("BlacktTransparent.png");
	blacksprite->setAnchorPoint(Point(0, 0.5));
	this->addChild(blacksprite, 7);
	blacksprite->setVisible(false);

	auto _mouseListener = EventListenerMouse::create();

	_mouseListener->onMouseMove = CC_CALLBACK_1(StartScene::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

void StartScene::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));


	Rect r1 = Rect(0, visibleSize.height * 3 / 5 - 50, visibleSize.width, 100);
	Rect r2 = Rect(0, visibleSize.height * 3 / 5 - 250, visibleSize.width, 100);
	Rect r3 = Rect(0, visibleSize.height * 3 / 5 - 450, visibleSize.width, 100);
	CallFunc* setMove = CallFunc::create([&]() {
		move = !move;
		});

	if (r1.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if (!move) {
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
			if (!move) {
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
			if (!move) {
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
		if (blacksprite->isVisible()) {
			CallFunc* func1 = CallFunc::create([&]() {
				blacksprite->setVisible(false);
				});
			auto fadeout = FadeOut::create(0.1f);
			auto seq = Sequence::create(fadeout, func1, nullptr);
			blacksprite->runAction(seq);
		}
	}
}

void StartScene::onEnterTransitionDidFinish()
{
	initMusic();
}
