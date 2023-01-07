#include "PlayerSetup.h"
#include"Scene/BackgroundChoise.h"
#include"Scene/Loading.h"
#include"Manager/GameManager.h"
#include"Sprite/CharacterBase.h"
#include"Sprite/Player2.h"
#include"Scene/AfterGame.h"


bool PlayerSetup::init() {

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	manager = UserManager::getInstance();

	//创建背景
	auto background = Sprite::create("playerMenu/background.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);;
	this->addChild(background);

	//布置按钮
	//back按钮
	auto BackToMenuButton = ui::Button::create("playerMenu/backUnselected.png", "playerMenu/backSelected.png");
	BackToMenuButton->setScale(1.0f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, origin.y + 1440 - 1230));
	this->addChild(BackToMenuButton);
	//continue
	auto Continue = ui::Button::create("playerMenu/continueUnselected.png", "playerMenu/continueSelected.png");
	Continue->setScale(1.0f);
	Continue->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::buttonCotinue, this));
	Continue->setPosition(Vec2(origin.x + visibleSize.width * 1690 / 2560, origin.y + 1440 - 1230));
	this->addChild(Continue);
	//player1的一系列
	auto pattern1 = PlayerPattern(1);
	pattern1->setPosition(Vec2(origin.x + 695, origin.y + 735));
	this->addChild(pattern1);

	auto UserID1 = ui::Button::create("playerMenu/UserID.png", "playerMenu/UserIDOn.png");
	UserID1->setScale(1.0f);
	UserID1->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::UserID1, this));
	UserID1->setPosition(Vec2(origin.x + visibleSize.width * 350 / 2560, origin.y + 1440 - 620));
	this->addChild(UserID1);

	auto bodycolor1 = ui::Button::create("playerMenu/bodycolorBotton.png", "playerMenu/bodycolorBottonOn.png");
	bodycolor1->setScale(1.0f);
	bodycolor1->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::bodyColor1, this));
	bodycolor1->setPosition(Vec2(origin.x + visibleSize.width * 350 / 2560, origin.y + 1440 - 740));
	this->addChild(bodycolor1);

	auto decoration1 = ui::Button::create("playerMenu/decoBotton.png", "playerMenu/decoBottonOn.png");
	decoration1->setScale(1.0f);
	decoration1->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::Deco1, this));
	decoration1->setPosition(Vec2(origin.x + visibleSize.width * 1040/ 2560, origin.y + 1440 - 620));
	this->addChild(decoration1);

	auto face1 = ui::Button::create("playerMenu/faceBotton.png", "playerMenu/faceBottonOn.png");
	face1->setScale(1.0f);
	face1->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::face1, this));
	face1->setPosition(Vec2(origin.x + visibleSize.width * 1040 / 2560, origin.y + 1440 - 740));
	this->addChild(face1);

	auto ai1 = Button::create("playerMenu/aiplayerBotton.png", "playerMenu/aiplayerSelected.png");
	ai1->setPosition(Vec2(origin.x + visibleSize.width * 350 / 2560, 1440 - 830));
	auto human1 = Button::create("playerMenu/humanplayerBotton.png", "playerMenu/humanplayerSelected.png");
	human1->setPosition(Vec2(origin.x + visibleSize.width * 350 / 2560, 1440 - 890));

	if (manager->player_type[1]) {
		ai1->loadTextureNormal("playerMenu/aiplayerBotton.png");
		human1->loadTextureNormal("playerMenu/humanplayerSelected.png");
	}
	else {
		ai1->loadTextureNormal("playerMenu/aiplayerSelected.png");
		human1->loadTextureNormal("playerMenu/humanplayerBotton.png");
	}

	//判断当前AI选择情况（3种：未选择，AI，human）  有了初始化.cpp后需要写这部分
	/*
	if(未选择）{}
	else if(AI）{
	    ai1->loadTextureNormal("playerMenu/aiplayerSelected.png");
		human1->loadTextureNormal("playerMenu/humanplayerBotton.png");
	}
	else{
		ai1->loadTextureNormal("playerMenu/aiplayerBotton.png");
		human1->loadTextureNormal("playerMenu/humanplayerSelected.png");
	}
	*/

	ai1->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		manager->player_type[1] = false;
		ai1->loadTextureNormal("playerMenu/aiplayerSelected.png");
		human1->loadTextureNormal("playerMenu/humanplayerBotton.png");
		});
	human1->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		manager->player_type[1] = true;
		ai1->loadTextureNormal("playerMenu/aiplayerBotton.png");
		human1->loadTextureNormal("playerMenu/humanplayerSelected.png");
		});
	this->addChild(ai1);
	this->addChild(human1);

	

	//player2
	auto pattern2 = PlayerPattern(2);
	pattern2->setPosition(Vec2(origin.x + 1865, origin.y + 735));
	this->addChild(pattern2);

	auto UserID2 = ui::Button::create("playerMenu/UserID.png", "playerMenu/UserIDOn.png");
	UserID2->setScale(1.0f);
	UserID2->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::UserID2, this));
	UserID2->setPosition(Vec2(origin.x + visibleSize.width * (350+1170) / 2560, origin.y + 1440 - 620));
	this->addChild(UserID2);

	auto bodycolor2 = ui::Button::create("playerMenu/bodycolorBotton.png", "playerMenu/bodycolorBottonOn.png");
	bodycolor2->setScale(1.0f);
	bodycolor2->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::bodyColor2, this));
	bodycolor2->setPosition(Vec2(origin.x + visibleSize.width * (350+1170) / 2560, origin.y + 1440 - 740));
	this->addChild(bodycolor2);

	auto decoration2 = ui::Button::create("playerMenu/decoBotton.png", "playerMenu/decoBottonOn.png");
	decoration2->setScale(1.0f);
	decoration2->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::Deco2, this));
	decoration2->setPosition(Vec2(origin.x + visibleSize.width * (1040 + 1170) / 2560, origin.y + 1440 - 620));
	this->addChild(decoration2);

	auto face2 = ui::Button::create("playerMenu/faceBotton.png", "playerMenu/faceBottonOn.png");
	face2->setScale(1.0f);
	face2->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::face2, this));
	face2->setPosition(Vec2(origin.x + visibleSize.width * (1040 + 1170) / 2560, origin.y + 1440 - 740));
	this->addChild(face2);

	auto ai2 = Button::create("playerMenu/aiplayerBotton.png", "playerMenu/aiplayerSelected.png");
	ai2->setPosition(Vec2(origin.x + visibleSize.width * (350 + 1170) / 2560, 1440 - 830));
	auto human2 = Button::create("playerMenu/humanplayerBotton.png", "playerMenu/humanplayerSelected.png");
	human2->setPosition(Vec2(origin.x + visibleSize.width * (350 + 1170) / 2560, 1440 - 890));

	if (manager->player_type[2]) {
		ai2->loadTextureNormal("playerMenu/aiplayerBotton.png");
		human2->loadTextureNormal("playerMenu/humanplayerSelected.png");
	}
	else {
		ai2->loadTextureNormal("playerMenu/aiplayerSelected.png");
		human2->loadTextureNormal("playerMenu/humanplayerBotton.png");
	}

	//判断当前AI选择情况（3种：未选择，AI，human）  有了初始化.cpp后需要写这部分
	/*
	if(未选择）{}
	else if(AI）{
		ai1->loadTextureNormal("playerMenu/aiplayerSelected.png");
		human1->loadTextureNormal("playerMenu/humanplayerBotton.png");
	}
	else{
		ai1->loadTextureNormal("playerMenu/aiplayerBotton.png");
		human1->loadTextureNormal("playerMenu/humanplayerSelected.png");
	}
	*/

	ai2->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		manager->player_type[2] = false;
		ai2->loadTextureNormal("playerMenu/aiplayerSelected.png");
		human2->loadTextureNormal("playerMenu/humanplayerBotton.png");
		});
	human2->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		manager->player_type[2] = true;
		ai2->loadTextureNormal("playerMenu/aiplayerBotton.png");
		human2->loadTextureNormal("playerMenu/humanplayerSelected.png");
		});
	this->addChild(ai2);
	this->addChild(human2);

	return true;
}

Sprite* PlayerSetup::PlayerPattern(int tag)
{
	Sprite* player = new Sprite();

	Sprite* body = Sprite::createWithSpriteFrameName(GameManager::Bodys[manager->player_skin[tag]]);
	Sprite* head = Sprite::createWithSpriteFrameName(GameManager::Heads[manager->player_skin[tag]]);
	Sprite* hand1 = Sprite::createWithSpriteFrameName(GameManager::Hands[manager->player_skin[tag]]);
	Sprite* hand2 = Sprite::createWithSpriteFrameName(GameManager::Hands[manager->player_skin[tag]]);
	Sprite* foot1 = Sprite::createWithSpriteFrameName(GameManager::Feet[manager->player_skin[tag]]);
	Sprite* foot2 = Sprite::createWithSpriteFrameName(GameManager::Feet[manager->player_skin[tag]]);
	Sprite* face = Sprite::createWithSpriteFrameName(GameManager::Faces[manager->player_face[tag]]);
	Sprite* hat = GameManager::Hats[manager->player_hat[tag]]?
		Sprite::createWithSpriteFrameName(GameManager::Hats[manager->player_hat[tag]]): new Sprite();

	/*body->setScale(2);
	head->setScale(2);
	hand1->setScale(2);
	hand2->setScale(2);
	foot1->setScale(2);
	foot2->setScale(2);
	face->setScale(2);*/

	head->setPosition(Vec2(65 / 2.2 - 8, 130 / 2.2 - 2));
	player->addChild(head, 1);

	hand1->setPosition(Vec2(-31 / 2.2, -55 / 2.2));
	player->addChild(hand1, 4);

	hat->setPosition(Vec2(0, 0) + head->getContentSize() / 2);
	head->addChild(hat, 3);

	face->setPosition(Vec2(0, 0) + head->getContentSize()/2);
	head->addChild(face, 2);

	hand2->setPosition(Vec2(109 / 2.2, -29 / 2.2));
	player->addChild(hand2, -1);

	foot1->setPosition(Vec2(-67 / 2.2, -199 / 2.2));
	foot1->setAnchorPoint(Vec2(0.2, 0.25));
	player->addChild(foot1, 3);

	foot2->setPosition(Vec2(33 / 2.2, -169 / 2.2));
	foot2->setAnchorPoint(Vec2(0.2, 0.25));
	player->addChild(foot2, -1);

	body->setPosition(Vec2(0, 0));
	player->addChild(body, 0);

	player->setScale(2);

	return player;
}

//----------------------------------Back and Continue--------------------------------------------------------
void PlayerSetup::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(Transition::create(0.5f,BackgroundChoise::create()));
		break;
	default:
		break;
	}
}

void PlayerSetup::buttonCotinue(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		if (manager->player1 == "" && find(manager->UserName.begin(), manager->UserName.end(), "") == manager->UserName.end()) {
			manager->UserName.push_back("");
			manager->Standing.insert(std::pair<std::string, std::vector<double>>("", { 0,0,0,0,0,0,0 }));
		}
		if (manager->player2 == "" && find(manager->UserName.begin(), manager->UserName.end(), "") == manager->UserName.end()) {
			manager->UserName.push_back("");
			manager->Standing.insert(std::pair<std::string, std::vector<double>>("", { 0,0,0,0,0,0,0 }));
		}

		Director::getInstance()->replaceScene(Transition::create(0.5f, GameScene::CreateGame(GameManager::BackChoise)));

		break;
	default:
		break;
	}
}

//----------------------------------UserID模块---------------------------------------------------------------------------------------------------------
void PlayerSetup::UserID1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);
	auto chooseBoard = Sprite::create("playerMenu/Id/nameBackground.png");
	chooseBoard->setPosition(1280, 1440 - 720);
	chooseBoard->setScale(1.0f);
	//Buttom
	auto backButton = Button::create("playerMenu/Id/back.png", "playerMenu/Id/backON.png");
	backButton->setPosition(Vec2(contentSize.width * (760 ) / 2560, 1440 - 620));
	auto confirm = Button::create("playerMenu/Id/confirm.png", "playerMenu/Id/confirmON.png");
	confirm->setPosition(Vec2(contentSize.width * (1800) / 2560, 1440 - 620));
	backButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(PlayerSetup::create());
		});
	
	////文本框
	auto inputBox = Sprite::create("playerMenu/Id/textSquare.png");
	auto editbox = EditBox::create(Size(inputBox->getContentSize().width, inputBox->getContentSize().height), Scale9Sprite::create("playerMenu/Id/textSquare.png"));
	editbox->setPosition(Vec2(1280, 1440 - 760));
	editbox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	editbox->setFont("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 70);
	editbox->setTextHorizontalAlignment(TextHAlignment::CENTER);
	confirm->addClickEventListener([=](Ref* sender) {
		auto text = editbox->getText();
		std::string name = text;
		if (find(manager->UserName.begin(), manager->UserName.end(), name) == manager->UserName.end()) {
			manager->UserName.push_back(name);
			manager->Standing.insert(std::pair<std::string, std::vector<double>>(name, { 0,0,0,0,0,0,0 }));
		}
		manager->player1 = name;
		//manager->Standing[name][3] += 1;//对局数+1

		manager->player_name[1] = text;

		Director::getInstance()->replaceScene(PlayerSetup::create());
		});
	
	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(backButton);
		this->addChild(confirm);
		this->addChild(editbox);

		break;
	default:
		break;
	}
}

void PlayerSetup::UserID2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);
	auto chooseBoard = Sprite::create("playerMenu/Id/nameBackground.png");
	chooseBoard->setPosition(1280, 1440 - 720);
	chooseBoard->setScale(1.0f);
	//Buttom
	auto backButton = Button::create("playerMenu/Id/back.png", "playerMenu/Id/backON.png");
	backButton->setPosition(Vec2(contentSize.width * (760) / 2560, 1440 - 620));
	auto confirm = Button::create("playerMenu/Id/confirm.png", "playerMenu/Id/confirmON.png");
	confirm->setPosition(Vec2(contentSize.width * (1800) / 2560, 1440 - 620));
	backButton->addClickEventListener([=](Ref* sender) {
		Director::getInstance()->replaceScene(PlayerSetup::create());
		});
	
	////文本框
	auto inputBox = Sprite::create("playerMenu/Id/textSquare.png");
	auto editbox = EditBox::create(Size(inputBox->getContentSize().width, inputBox->getContentSize().height), Scale9Sprite::create("playerMenu/Id/textSquare.png"));
	editbox->setPosition(Vec2(1280, 1440 - 760));
	editbox->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	editbox->setFont("fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF",70);
	editbox->setTextHorizontalAlignment(TextHAlignment::CENTER);//居中
	

	confirm->addClickEventListener([=](Ref* sender) {
		auto text = editbox->getText();
		log(text);
		std::string name = text;
		if (find(manager->UserName.begin(), manager->UserName.end(), name) == manager->UserName.end()) {
			manager->UserName.push_back(name);
			manager->Standing.insert(std::pair<std::string, std::vector<double>>(name, { 0,0,0,0,0,0,0 }));
		}
		manager->player2 = name;
		//manager->Standing[name][3] += 1;//对局数+1

		manager->player_name[2] = text;

		Director::getInstance()->replaceScene(PlayerSetup::create());
		});
	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(backButton);
		this->addChild(confirm);
		this->addChild(editbox);
		break;
	default:
		break;
	}
}

//------------------------Color模块------------------------PLAYER1-----------------------------------------------------------------------------
void PlayerSetup::SQblack1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "Black";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}

void PlayerSetup::SQblue1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "Blue";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQgreen1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "Green";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQpink1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "Pink";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQpurple1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "Purple";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQred1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "Red";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQwhite1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "White";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQyellow1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[1] = "Yellow";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}


void PlayerSetup::bodyColor1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);

	auto chooseBoard = Sprite::create("playerMenu/choose/chooseBoard.png");
	chooseBoard->setPosition(1280, 1440 - 720);
	chooseBoard->setScale(1.0f);

	//按钮设置
	auto black = ui::Button::create("playerMenu/color/SQblack.png", "playerMenu/color/SQblack.png");
	black->setScale(1.0f);
	black->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQblack1, this));
	black->setPosition(Vec2(contentSize.width * 790 / 2560, 1440 - 720));

	auto SQblue = ui::Button::create("playerMenu/color/SQblue.png", "playerMenu/color/SQblue.png");
	SQblue->setScale(1.0f);
	SQblue->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQblue1, this));
	SQblue->setPosition(Vec2(contentSize.width * 930 / 2560, 1440 - 720));
	auto SQgreen = ui::Button::create("playerMenu/color/SQgreen.png", "playerMenu/color/SQgreen.png");
	SQgreen->setScale(1.0f);
	SQgreen->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQgreen1, this));
	SQgreen->setPosition(Vec2(contentSize.width * 1070 / 2560, 1440 - 720));
	auto SQpink = ui::Button::create("playerMenu/color/SQpink.png", "playerMenu/color/SQpink.png");
	SQpink->setScale(1.0f);
	SQpink->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQpink1, this));
	SQpink->setPosition(Vec2(contentSize.width * 1210 / 2560, 1440 - 720));
	auto SQpurple = ui::Button::create("playerMenu/color/SQpurple.png", "playerMenu/color/SQpurple.png");
	SQpurple->setScale(1.0f);
	SQpurple->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQpurple1, this));
	SQpurple->setPosition(Vec2(contentSize.width * 1350 / 2560, 1440 - 720));
	auto SQred = ui::Button::create("playerMenu/color/SQred.png", "playerMenu/color/SQred.png");
	SQred->setScale(1.0f);
	SQred->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQred1, this));
	SQred->setPosition(Vec2(contentSize.width * 1490 / 2560, 1440 - 720));
	auto SQwhite = ui::Button::create("playerMenu/color/SQwhite.png", "playerMenu/color/SQwhite.png");
	SQwhite->setScale(1.0f);
	SQwhite->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQwhite1, this));
	SQwhite->setPosition(Vec2(contentSize.width * 1630 / 2560, 1440 - 720));
	auto SQyellow = ui::Button::create("playerMenu/color/SQyellow.png", "playerMenu/color/SQyellow.png");
	SQyellow->setScale(1.0f);
	SQyellow->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQyellow1, this));
	SQyellow->setPosition(Vec2(contentSize.width * 1770 / 2560, 1440 - 720));

	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(black);
		this->addChild(SQblue);
		this->addChild(SQgreen);
		this->addChild(SQpink);
		this->addChild(SQpurple);
		this->addChild(SQred);
		this->addChild(SQwhite);
		this->addChild(SQyellow);

		break;
	default:
		break;
	}
}

//------------------------Color模块------------------------PLAYER2-----------------------------------------------------------------------------
void PlayerSetup::SQblack2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "Black";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}

void PlayerSetup::SQblue2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "Blue";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQgreen2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "Green";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQpink2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "Pink";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQpurple2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "Purple";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQred2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "Red";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQwhite2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "White";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::SQyellow2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_skin[2] = "Yellow";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}

void PlayerSetup::bodyColor2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);

	auto chooseBoard = Sprite::create("playerMenu/choose/chooseBoard.png");
	chooseBoard->setPosition(1280, 1440 - 720);
	chooseBoard->setScale(1.0f);

	//按钮设置
	auto black = ui::Button::create("playerMenu/color/SQblack.png", "playerMenu/color/SQblack.png");
	black->setScale(1.0f);
	black->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQblack2, this));
	black->setPosition(Vec2(contentSize.width * 790 / 2560, 1440 - 720));

	auto SQblue = ui::Button::create("playerMenu/color/SQblue.png", "playerMenu/color/SQblue.png");
	SQblue->setScale(1.0f);
	SQblue->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQblue2, this));
	SQblue->setPosition(Vec2(contentSize.width * 930 / 2560, 1440 - 720));
	auto SQgreen = ui::Button::create("playerMenu/color/SQgreen.png", "playerMenu/color/SQgreen.png");
	SQgreen->setScale(1.0f);
	SQgreen->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQgreen2, this));
	SQgreen->setPosition(Vec2(contentSize.width * 1070 / 2560, 1440 - 720));
	auto SQpink = ui::Button::create("playerMenu/color/SQpink.png", "playerMenu/color/SQpink.png");
	SQpink->setScale(1.0f);
	SQpink->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQpink2, this));
	SQpink->setPosition(Vec2(contentSize.width * 1210/ 2560, 1440 - 720));
	auto SQpurple = ui::Button::create("playerMenu/color/SQpurple.png", "playerMenu/color/SQpurple.png");
	SQpurple->setScale(1.0f);
	SQpurple->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQpurple2, this));
	SQpurple->setPosition(Vec2(contentSize.width * 1350 / 2560, 1440 - 720));
	auto SQred = ui::Button::create("playerMenu/color/SQred.png", "playerMenu/color/SQred.png");
	SQred->setScale(1.0f);
	SQred->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQred2, this));
	SQred->setPosition(Vec2(contentSize.width * 1490 / 2560, 1440 - 720));
	auto SQwhite = ui::Button::create("playerMenu/color/SQwhite.png", "playerMenu/color/SQwhite.png");
	SQwhite->setScale(1.0f);
	SQwhite->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQwhite2, this));
	SQwhite->setPosition(Vec2(contentSize.width * 1630 / 2560, 1440 - 720));
	auto SQyellow = ui::Button::create("playerMenu/color/SQyellow.png", "playerMenu/color/SQyellow.png");
	SQyellow->setScale(1.0f);
	SQyellow->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::SQyellow2, this));
	SQyellow->setPosition(Vec2(contentSize.width * 1770 / 2560, 1440 - 720));

	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(black);
		this->addChild(SQblue);
		this->addChild(SQgreen);
		this->addChild(SQpink);
		this->addChild(SQpurple);
		this->addChild(SQred);
		this->addChild(SQwhite);
		this->addChild(SQyellow);

		break;
	default:
		break;
	}
}




//-------------*********----------Deco模块---------------------PLAYER1------------------------------------------------------------------------------------------------
void PlayerSetup::DECdrop1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[1] = "Drop";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECtire1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[1] = "Tie";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECblackhat1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[1] = "BlackHat";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECwhitehat1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[1] = "WhiteHat";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECangel1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[1] = "Angel";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}

void PlayerSetup::Deco1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);

	auto chooseBoard = Sprite::create("playerMenu/choose/chooseBoard.png");
	chooseBoard->setPosition(1280, 1440-720);
	chooseBoard->setScale(1.0f);

	//按钮设置
	auto decdrop = ui::Button::create("playerMenu/choose/DECdrop.png", "playerMenu/choose/DECdrop.png");
	decdrop->setScale(1.0f);
	decdrop->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECdrop1, this));
	decdrop->setPosition(Vec2(contentSize.width * 840 / 2560, 1440 - 720));

	auto dectire = ui::Button::create("playerMenu/choose/DECtire.png", "playerMenu/choose/DECtire.png");
	dectire->setScale(1.0f);
	dectire->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECtire1, this));
	dectire->setPosition(Vec2(contentSize.width * 1060 / 2560, 1440 - 720));

	auto decblackhat = ui::Button::create("playerMenu/choose/DECblackhat.png", "playerMenu/choose/DECblackhat.png");
	decblackhat->setScale(1.0f);
	decblackhat->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECblackhat1, this));
	decblackhat->setPosition(Vec2(contentSize.width * 1287 / 2560, 1440 - 704));

	auto decwhitehat = ui::Button::create("playerMenu/choose/DECwhitehat.png", "playerMenu/choose/DECwhitehat.png");
	decwhitehat->setScale(1.0f);
	decwhitehat->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECwhitehat1, this));
	decwhitehat->setPosition(Vec2(contentSize.width * 1490.3 / 2560, 1440 - 705.4));

	auto decangel = ui::Button::create("playerMenu/choose/DECangel.png", "playerMenu/choose/DECangel.png");
	decangel->setScale(1.0f);
	decangel->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECangel1, this));
	decangel->setPosition(Vec2(contentSize.width * 1720 / 2560, 1440 - 714.25));
	
	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(decdrop);
		this->addChild(dectire);
		this->addChild(decblackhat);
		this->addChild(decwhitehat);
		this->addChild(decangel);
		
		break;
	default:
		break;
	}
}

//----------------------Deco模块-----------------player2-----------------------------------------------------------
void PlayerSetup::DECdrop2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[2] = "Drop";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECtire2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[2] = "Tie";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECblackhat2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[2] = "BlackHat";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECwhitehat2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[2] = "WhiteHat";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::DECangel2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_hat[2] = "Angel";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}

void PlayerSetup::Deco2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);

	auto chooseBoard = Sprite::create("playerMenu/choose/chooseBoard.png");
	chooseBoard->setPosition(1280, 1440 - 720);
	chooseBoard->setScale(1.0f);

	//按钮设置
	auto decdrop = ui::Button::create("playerMenu/choose/DECdrop.png", "playerMenu/choose/DECdrop.png");
	decdrop->setScale(1.0f);
	decdrop->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECdrop2, this));
	decdrop->setPosition(Vec2(contentSize.width * 840 / 2560, 1440 - 720));

	auto dectire = ui::Button::create("playerMenu/choose/DECtire.png", "playerMenu/choose/DECtire.png");
	dectire->setScale(1.0f);
	dectire->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECtire2, this));
	dectire->setPosition(Vec2(contentSize.width * 1060 / 2560, 1440 - 720));

	auto decblackhat = ui::Button::create("playerMenu/choose/DECblackhat.png", "playerMenu/choose/DECblackhat.png");
	decblackhat->setScale(1.0f);
	decblackhat->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECblackhat2, this));
	decblackhat->setPosition(Vec2(contentSize.width * 1287 / 2560, 1440 - 704));

	auto decwhitehat = ui::Button::create("playerMenu/choose/DECwhitehat.png", "playerMenu/choose/DECwhitehat.png");
	decwhitehat->setScale(1.0f);
	decwhitehat->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECwhitehat2, this));
	decwhitehat->setPosition(Vec2(contentSize.width * 1490.3 / 2560, 1440 - 705.4));

	auto decangel = ui::Button::create("playerMenu/choose/DECangel.png", "playerMenu/choose/DECangel.png");
	decangel->setScale(1.0f);
	decangel->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::DECangel2, this));
	decangel->setPosition(Vec2(contentSize.width * 1720 / 2560, 1440 - 714.25));

	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(decdrop);
		this->addChild(dectire);
		this->addChild(decblackhat);
		this->addChild(decwhitehat);
		this->addChild(decangel);

		break;
	default:
		break;
	}
}

//-------------*********----------face模块---------------------PLAYER1------------------------------------------------------------------------------------------------
void PlayerSetup::FCcross1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[1] = "Cross";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCglass1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[1] = "Glass";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCnormal1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[1] = "Normal";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCsmiledot1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[1] = "Dot";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCsmiletiebag1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[1] = "Smile";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}

void PlayerSetup::face1(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);

	auto chooseBoard = Sprite::create("playerMenu/choose/chooseBoard.png");
	chooseBoard->setPosition(1280, 1440 - 720);
	chooseBoard->setScale(1.0f);

	//按钮设置
	auto FCcross = ui::Button::create("playerMenu/face/FCcross.png", "playerMenu/face/FCcross.png");
	FCcross->setScale(1.0f);
	FCcross->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCcross1, this));
	FCcross->setPosition(Vec2(contentSize.width * 840 / 2560, 1440 - 720));

	auto FCglass = ui::Button::create("playerMenu/face/FCglass.png", "playerMenu/face/FCglass.png");
	FCglass->setScale(1.0f);
	FCglass->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCglass1, this));
	FCglass->setPosition(Vec2(contentSize.width * 1060 / 2560, 1440 - 720));
	auto FCnormal = ui::Button::create("playerMenu/face/FCnormal.png", "playerMenu/face/FCnormal.png");
	FCnormal->setScale(1.0f);
	FCnormal->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCnormal1, this));
	FCnormal->setPosition(Vec2(contentSize.width * 1280 / 2560, 1440 - 720));
	auto FCsmiledot = ui::Button::create("playerMenu/face/FCsmiledot.png", "playerMenu/face/FCsmiledot.png");
	FCsmiledot->setScale(1.0f);
	FCsmiledot->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCsmiledot1, this));
	FCsmiledot->setPosition(Vec2(contentSize.width * 1500 / 2560, 1440 - 720));
	auto FCsmiletiebag = ui::Button::create("playerMenu/face/FCsmiletieba.png", "playerMenu/face/FCsmiletieba.png");
	FCsmiletiebag->setScale(1.0f);
	FCsmiletiebag->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCsmiletiebag1, this));
	FCsmiletiebag->setPosition(Vec2(contentSize.width * 1720 / 2560, 1440 - 720));

	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(FCcross);
		this->addChild(FCglass);
		this->addChild(FCnormal);
		this->addChild(FCsmiledot);
		this->addChild(FCsmiletiebag);

		break;
	default:
		break;
	}
}


//-------------*********----------face模块---------------------PLAYER1------------------------------------------------------------------------------------------------
void PlayerSetup::FCcross2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[2] = "Cross";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCglass2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[2] = "Glass";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCnormal2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[2] = "Normal";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCsmiledot2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[2] = "Dot";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::FCsmiletiebag2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//在 初始化.cpp 里初始化信息
		manager->player_face[2] = "Smile";

		//回去
		Director::getInstance()->replaceScene(PlayerSetup::create());
		break;
	default:
		break;
	}
}
void PlayerSetup::face2(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto back = Sprite::create("playerMenu/choose/back.png");
	back->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	back->setPosition(0, 0);
	auto contentSize = back->getContentSize();
	back->setScale(1.0f);

	auto chooseBoard = Sprite::create("playerMenu/choose/chooseBoard.png");
	chooseBoard->setPosition(1280, 1440 - 720);
	chooseBoard->setScale(1.0f);

	//按钮设置
	auto FCcross = ui::Button::create("playerMenu/face/FCcross.png", "playerMenu/face/FCcross.png");
	FCcross->setScale(1.0f);
	FCcross->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCcross2, this));
	FCcross->setPosition(Vec2(contentSize.width * 840 / 2560, 1440 - 720));

	auto FCglass = ui::Button::create("playerMenu/face/FCglass.png", "playerMenu/face/FCglass.png");
	FCglass->setScale(1.0f);
	FCglass->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCglass2, this));
	FCglass->setPosition(Vec2(contentSize.width * 1060 / 2560, 1440 - 720));
	auto FCnormal = ui::Button::create("playerMenu/face/FCnormal.png", "playerMenu/face/FCnormal.png");
	FCnormal->setScale(1.0f);
	FCnormal->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCnormal2, this));
	FCnormal->setPosition(Vec2(contentSize.width * 1280 / 2560, 1440 - 720));
	auto FCsmiledot = ui::Button::create("playerMenu/face/FCsmiledot.png", "playerMenu/face/FCsmiledot.png");
	FCsmiledot->setScale(1.0f);
	FCsmiledot->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCsmiledot2, this));
	FCsmiledot->setPosition(Vec2(contentSize.width * 1500 / 2560, 1440 - 720));
	auto FCsmiletiebag = ui::Button::create("playerMenu/face/FCsmiletieba.png", "playerMenu/face/FCsmiletieba.png");
	FCsmiletiebag->setScale(1.0f);
	FCsmiletiebag->addTouchEventListener(CC_CALLBACK_2(PlayerSetup::FCsmiletiebag2, this));
	FCsmiletiebag->setPosition(Vec2(contentSize.width * 1720 / 2560, 1440 - 720));

	switch (type) {
	case Widget::TouchEventType::ENDED:
		this->addChild(back);
		this->addChild(chooseBoard);
		this->addChild(FCcross);
		this->addChild(FCglass);
		this->addChild(FCnormal);
		this->addChild(FCsmiledot);
		this->addChild(FCsmiletiebag);

		break;
	default:
		break;
	}
}

