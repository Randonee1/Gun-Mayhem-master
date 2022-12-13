#include "Background.h"
#include"Scene/GameScene.h"

Background* Background::createGame()
{
	auto layer = new Background();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

	return NULL;
}

bool Background::init()
{
	if (!MapBase::init()) {
		return false;
	}
	initBackground();

	floor_height = 260;
	floor_base = 150;
	Floor = { {688,1224},{0,289,522,1366,1599,1890},{289,1599},{522,1366} };
	death_line = -1000;

	initPlayer();

	packageEvent = PackageEvent::create(this);

	this->scheduleUpdate();

	return true;
}

void Background::update(float dt)
{
	Vec2 initPlatform = Vec2(platformSize.width / 2, (floor_base + floor_base + floor_height * (Floor.size() - 1)) / 2);
	Vec2 delta = Vec2(0, 0);
	for (auto& player : players) { delta += player->getPosition(); }
	delta = delta / players.size() - initPlatform;

	float a = std::pow(delta.x, 2) + std::pow(delta.y, 2);
	float b = std::pow(visibleSize.height / 1.5, 2) + std::pow(visibleSize.width / 1.5, 2);
	if (a > b) {
		delta.x = delta.x * b / a;
		delta.y = delta.y * b / a;
	}

	backLayer->setPosition(initbackLayerPosition - delta * 0.1);
	mountain1->setPosition(initMountain1Position - delta * 0.2);
	city1->setPosition(initCity1Position - delta * 0.3);
	city2->setPosition(initCity2Position - delta * 0.4);
	city3->setPosition(initCity3Position - delta * 0.5);
	mountain2->setPosition(initMountain2Position - delta * 0.6);
	platform->setPosition(initPlatformPosition - delta * 0.7);

	ShotEvent();

	packageEvent->update(dt);
	packageEvent->PackageUpdate(players);
}

void Background::initBackground()
{
	backLayer = Sprite::create("sunset/background.png");
	auto backLayer_left = Sprite::create("sunset/background.png");
	auto backLayer_right = Sprite::create("sunset/background.png");
	auto sun = Sprite::create("sunset/sun.png");
	initbackLayerPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	backLayer_left->setPosition(-backLayer->getContentSize().width / 2, backLayer->getContentSize().height / 2);
	backLayer_right->setPosition(backLayer->getContentSize().width * 3 / 2, backLayer->getContentSize().height / 2);
	sun->setPosition(backLayer->getContentSize().width / 2 - 400, backLayer->getContentSize().height / 2 + 200);
	backLayer->addChild(backLayer_right, 0);
	backLayer->addChild(backLayer_left, 0);
	backLayer->addChild(sun, 1);
	backLayer->setPosition(initbackLayerPosition);
	this->addChild(backLayer, 0);

	mountain1 = Sprite::create("sunset/mountain.png");
	auto mountain1_left = Sprite::create("sunset/mountain.png");
	auto mountain1_right = Sprite::create("sunset/mountain.png");
	initMountain1Position = Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200);
	mountain1_left->setPosition(-mountain1->getContentSize().width / 2, mountain1->getContentSize().height / 2);
	mountain1_right->setPosition(mountain1->getContentSize().width * 3 / 2, mountain1->getContentSize().height / 2);
	mountain1->addChild(mountain1_left, 0);
	mountain1->addChild(mountain1_right, 0);
	mountain1->setPosition(initMountain1Position);
	this->addChild(mountain1, 1);

	city1 = Sprite::create("sunset/city1.png");
	auto city1_left = Sprite::create("sunset/city1.png");
	auto city1_right = Sprite::create("sunset/city1.png");
	initCity1Position = Vec2(visibleSize.width / 2, visibleSize.height / 2 - 500);
	city1_left->setPosition(-city1->getContentSize().width / 2, city1->getContentSize().height / 2);
	city1_right->setPosition(city1->getContentSize().width * 3 / 2, city1->getContentSize().height / 2);
	city1->addChild(city1_left, 0);
	city1->addChild(city1_right, 0);
	city1->setPosition(initCity1Position);
	this->addChild(city1, 2);

	city2 = Sprite::create("sunset/city2.png");
	auto city2_left = Sprite::create("sunset/city2.png");
	auto city2_right = Sprite::create("sunset/city2.png");
	initCity2Position = Vec2(visibleSize.width / 2 + 500, visibleSize.height / 2 - 300);
	city2_left->setPosition(-city2->getContentSize().width / 2, city2->getContentSize().height / 2);
	city2_right->setPosition(city2->getContentSize().width * 3 / 2, city2->getContentSize().height / 2);
	city2->setPosition(initCity2Position);
	city2->addChild(city2_left, 0);
	city2->addChild(city2_right, 0);
	this->addChild(city2, 3);

	city3 = Sprite::create("sunset/city3.png");
	auto city3_left = Sprite::create("sunset/city3.png");
	auto city3_right = Sprite::create("sunset/city3.png");
	initCity3Position = Vec2(visibleSize.width / 2, visibleSize.height / 2 - 300);
	city3_left->setPosition(-city3->getContentSize().width / 2 - 150, city3->getContentSize().height / 2);
	city3_right->setPosition(city3->getContentSize().width * 3 / 2 + 150, city3->getContentSize().height / 2);
	city3->setPosition(initCity3Position);
	city3->addChild(city3_left, 0);
	city3->addChild(city3_right, 0);
	this->addChild(city3, 4);

	mountain2 = Sprite::create("sunset/mountain.png");
	auto mountain2_left = Sprite::create("sunset/mountain.png");
	auto mountain2_right = Sprite::create("sunset/mountain.png");
	initMountain2Position = Vec2(visibleSize.width / 2, visibleSize.height / 2 - 700);
	mountain2_left->setPosition(-mountain2->getContentSize().width / 2 + 510, mountain2->getContentSize().height / 2);
	mountain2_right->setPosition(mountain2->getContentSize().width * 3 / 2 - 510, mountain2->getContentSize().height / 2);
	/*mountain2_left->setFlippedX(true);
	mountain2_right->setFlippedX(true);*/
	mountain2->addChild(mountain2_left, 0);
	mountain2->addChild(mountain2_right, -1);
	mountain2->setPosition(initMountain2Position);
	this->addChild(mountain2, 5);

	platform = Sprite::create("sunset/platform.png");
	initPlatformPosition = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	platform->setPosition(initPlatformPosition);
	this->addChild(platform, 6);
	platformSize = platform->getContentSize();

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
	this->addChild(label,8);


	//设置菜单项
	//文字菜单项
	MenuItemFont* GameMenu = MenuItemFont::create("Game Begin", [&](Ref* sender) {
		auto scene = GameScene::CreateGame(1);
		Director::getInstance()->replaceScene(scene);
		//Director::getInstance()->replaceScene(Loading::createScene());
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
	auto menu = Menu::create(GameMenu, SettingMenu, WeaponMenu, NULL);
	menu->setPosition(Vec2(origin.x + visibleSize.width * 6 / 7, origin.y + visibleSize.height * 3 / 5));
	this->addChild(menu, 8);


	//鼠标监听器//GameBegin的监听
	blacksprite = Sprite::create("BlacktTransparent.png");
	blacksprite->setAnchorPoint(Point(0, 0.5));
	this->addChild(blacksprite,7);
	blacksprite->setVisible(false);

	auto _mouseListener = EventListenerMouse::create();

	_mouseListener->onMouseMove = CC_CALLBACK_1(Background::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

}

void Background::initPlayer()
{
	/*CharacterBase* player1 = Player1::createWithTag(1, this);
	platform->addChild(player1, 1);*/

	CharacterBase* player1 = AI1::create(1,this);
	platform->addChild(player1, 1);

	CharacterBase* player2 = AI1::create(2, this);
	platform->addChild(player2, 2);

	/*CharacterBase* player2 = Player1::createWithTag(2, this);
	platform->addChild(player2, 2);*/

	player1->GetOpponent(player2);
	player2->GetOpponent(player1);

	players.push_back(player1);
	players.push_back(player2);
}

void Background::ShotEvent()
{
	std::vector<Bullet*> temp;
	for (auto bullet : bullets) {
		if (bullet)
			temp.push_back(bullet);
	}
	bullets = temp;

	for (auto& bullet : bullets) {

		if (bullet->getPositionX() > 12000 || bullet->getPositionX() < -6000) {
			bullet->removeFromParent();
			bullet = nullptr;
			continue;
		}
		for (auto& player : players) {

			auto rect = player->body->organ->getBoundingBox();
			Vec2 offset = player->getPosition() + player->body->getPosition();
			rect.origin += offset;

			if (rect.containsPoint(bullet->getPosition()) && player->valid) {
				player->x_speed += bullet->hitSpeed;
				player->hit = true;
				auto blood = Blood::create();
				blood->setPosition(bullet->getPosition());
				platform->addChild(blood, 4);

				bullet->removeFromParent();
				bullet = nullptr;
				break;
			}
		}
	}
}


//设置鼠标监听，用于滑条的显示。这里的鼠标监听类型为onMouseMove
void Background::onMouseMove(Event* event)
{
	EventMouse* e = (EventMouse*)event;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));


	Rect r1 = Rect(0, visibleSize.height * 3 / 5 - 50, visibleSize.width , 100);
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