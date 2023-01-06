#include "StartScene.h" 
#include"Scene/Loading.h"
#include"Scene/Credits.h"
#include"Scene/Standing.h"
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
	initFile();

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

	manager->player_skin[1] = manager->SkinRandom();
	manager->player_skin[2] = manager->SkinRandom();

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

	manager->player_face[1] = "Normal";
	manager->player_face[2] = "Normal";

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
	SettingMenu->setPosition(0, -140);


	MenuItemFont* WeaponMenu = MenuItemFont::create("Weapon", [&](Ref* sender) {
		//Director::getInstance()->replaceScene(setting::createScene());
		});
	WeaponMenu->setColor(Color3B::WHITE);
	WeaponMenu->setFontNameObj("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF");
	WeaponMenu->setFontSizeObj(100);
	WeaponMenu->setPosition(0, -280);

	MenuItemFont* StandingMenu = MenuItemFont::create("Standing", [&](Ref* sender) {
		Director::getInstance()->replaceScene(Transition::create(0.5f, Standing::createScene()));
		});
	StandingMenu->setColor(Color3B::WHITE);
	StandingMenu->setFontNameObj("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF");
	StandingMenu->setFontSizeObj(100);
	StandingMenu->setPosition(0, -500);

	MenuItemFont* creditsMenu = MenuItemFont::create("Credits", [&](Ref* sender) {
		Director::getInstance()->replaceScene(Transition::create(0.5f, Credits::createScene()));
		});
	creditsMenu->setColor(Color3B::WHITE);
	creditsMenu->setFontNameObj("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF");
	creditsMenu->setFontSizeObj(100);
	creditsMenu->setPosition(0, -640);



	//创建菜单
	auto menu = Menu::create(GameMenu, SettingMenu, WeaponMenu,StandingMenu,creditsMenu, NULL);
	menu->setPosition(Vec2(origin.x + visibleSize.width * 6 / 7, origin.y + visibleSize.height * 2 / 3));
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


	Rect r1 = Rect(0, visibleSize.height * 2 / 3 - 50, visibleSize.width, 140);
	Rect r2 = Rect(0, visibleSize.height * 2 / 3 - 190, visibleSize.width, 140);
	Rect r3 = Rect(0, visibleSize.height * 2 / 3 - 310, visibleSize.width, 140);
	Rect r4 = Rect(0, visibleSize.height * 2 / 3 - 550, visibleSize.width, 140);
	Rect r5 = Rect(0, visibleSize.height * 2 / 3 - 690, visibleSize.width, 140);
	CallFunc* setMove = CallFunc::create([&]() {
		move = !move;
		});

	if (r1.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if (!move) {
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 2 / 3)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 2 / 3));
			blacksprite->setVisible(true);
			auto fadein = FadeIn::create(0.1);
			blacksprite->runAction(fadein);
		}
	}
	else if (r2.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if (!move) {
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 2 / 3 - 140)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 2 / 3 - 140));
			blacksprite->setVisible(true);
			auto fadein = FadeIn::create(0.1);
			blacksprite->runAction(fadein);
		}
	}
	else if (r3.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if (!move) {
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 2 / 3 - 280)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 2 / 3 - 280));
			blacksprite->setVisible(true);
			auto fadein = FadeIn::create(0.1);
			blacksprite->runAction(fadein);
		}
	}
	else if (r4.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if (!move) {
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 2 / 3 - 500)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 2 / 3 - 500));
			blacksprite->setVisible(true);
			auto fadein = FadeIn::create(0.1);
			blacksprite->runAction(fadein);
		}
	}
	else if (r5.containsPoint(locationInNode)) {
		if (blacksprite->isVisible()) {
			if (!move) {
				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 2 / 3 - 640)));
				auto seq = Sequence::create(setMove, move, setMove, nullptr);
				seq->setTag(1);
				blacksprite->stopActionByTag(1);
				blacksprite->runAction(seq);
			}
		}
		else {
			blacksprite->setPosition(Vec2(0, visibleSize.height * 2 / 3 - 640));
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

void StartScene::initFile() {
	////写文件 后面注销掉就好
	//std::ofstream outClientFile("StandingFile.txt", std::ios::out);
	//if (!outClientFile) {
	//	log("File Write ERROR");
	//	std::exit(EXIT_FAILURE);
	//}
	//log("Write SUCCESS!");
	///*outClientFile << "name" <<" "<< 1<<" " << 2 <<" " << 3<<" " << 4<<" " << 5 <<" " << 6 << std::endl;
	//outClientFile << "name2" << " " << 19 << " " << 2.8767567 << " " << 3.8768765 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name3" << " " << 3324 << " " << 2.3242 << " " << 32 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name4" << " " << 321335 << " " << 12 << " " << 13 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name5" << " " << 12433 << " " << 32.52 << " " << 43 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name6" << " " << 24683 << " " << 49 << " " << 65.43 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name7" << " " << 97 << " " << 48.9 << " " << 56.246256<< " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name8" << " " << 9087 << " " << 21.2411 << " " << 31.2 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name9" << " " << 35 << " " << 223.12 << " " << 9.32 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name10" << " " << 308 << " " << 23.4 << " " << 76 << " " << 4 << " " << 5 << " " << 6 << std::endl;*/
	//outClientFile << "name11" << " " << 332980 << " " << 1.2 << " " <<89 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "name12" << " " << 123218 << " " << 2 << " " << 4 << " " << 4 << " " << 5 << " " << 6 << std::endl;
	//outClientFile << "aaaaaaa" << " " << 11.34255 << " " << 22.3543 << " " << 2<< " " << 44 << " " << 55 << " " << 66 << std::endl;
	//outClientFile.close();
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//读文件
	std::ifstream inClientFile("StandingFile.txt",std::ios::in);
	if (!inClientFile) {
		log("File Open Erro");
		std::exit(EXIT_FAILURE);
	}
	auto manager = UserManager::getInstance();
	std::string name;
	double mark;
	double rate;
	double kill_per_game;
	double num;
	double kill_this_game;
	double shot_this_game;

	while (inClientFile >> name >> mark >> rate >> kill_per_game >> num >> kill_this_game >> shot_this_game) {
		manager->UserName.push_back(name);
		manager->Standing.insert(std::pair<std::string, std::vector<double>>(name, { mark,rate,kill_per_game,num,kill_this_game,shot_this_game }));
	}


}
