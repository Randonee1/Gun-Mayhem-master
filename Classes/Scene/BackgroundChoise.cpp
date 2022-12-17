#include"Scene/BackgroundChoise.h"
#include"Scene/StartScene.h"
#include"Manager/GameManager.h"
#include<vector>
#include<time.h>

bool BackgroundChoise::init() {

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//创建背景
	auto background = Sprite::create("customGameMenu/background.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);;
	this->addChild(background);

	


	auto inputBox = Sprite::create("editbox.png");
	auto editbox1 = EditBox::create(Size(inputBox->getContentSize().width, inputBox->getContentSize().height), Scale9Sprite::create("editbox.png"));
	
	//auto editbox1 = EditBox::create(Size(200, 35), Scale9Sprite::create("editbox.png"));
	//editbox1->setAnchorPoint(Point(0, 0));
	editbox1->setPosition(Vec2(697, 1440-1064));
	editbox1->setPlaceHolder("name:");//占位字符
	//editbox1->setMaxLength(8);
	editbox1->setFontColor(Color3B::BLACK);//设置输入字体的颜色
	editbox1->setTag(1);
	this->addChild(editbox1, 2);

	auto text=editbox1->getText();
	int live = *text - '0';
	GameManager::Live = live;


	//布置按钮
	//back按钮
	auto BackToMenuButton = ui::Button::create("customGameMenu/backUnselected.png", "customGameMenu/backSelected.png");
	BackToMenuButton->setScale(1.0f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(BackgroundChoise::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, origin.y + 1440-1230));
	this->addChild(BackToMenuButton);
	//continue
	auto Continue = ui::Button::create("customGameMenu/continueUnselected.png", "customGameMenu/continueSelected.png");
	Continue->setScale(1.0f);
	Continue->addTouchEventListener(CC_CALLBACK_2(BackgroundChoise::buttonCotinue, this));
	Continue->setPosition(Vec2(origin.x + visibleSize.width * 1690 / 2560, origin.y + 1440 - 1230));
	this->addChild(Continue);

//=============================================\\地图选择//=================================================================================================
	auto Random = Button::create("customGameMenu/randomUnselected.png", "customGameMenu/randomSelected.png");
	Random->setPosition(Vec2(origin.x + visibleSize.width * 717.5 / 2560, 1440 - 420));

	auto spacestation = Button::create("customGameMenu/spacestationUnselected.png", "customGameMenu/spacestationSelected.png");
	spacestation->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440-530));

	auto sunsetcity = Button::create("customGameMenu/sunsetcityUnselected.png", "customGameMenu/sunsetcitySelected.png");
	sunsetcity->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440-610 ));

	auto seele = Button::create("customGameMenu/seeleUnselected.png", "customGameMenu/seeleSelected.png");
	seele->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 690));

	auto irismood = Button::create("customGameMenu/irismoodUnselected.png", "customGameMenu/irismoodSelected.png");
	irismood->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 770));

	auto highmoon = Button::create("customGameMenu/highmoonUnselected.png", "customGameMenu/highmoonSelected.png");
	highmoon->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 850));

	auto Default = Button::create("customGameMenu/defaultUnselected.png", "customGameMenu/defaultSelected.png");
	Default->setPosition(Vec2(origin.x + visibleSize.width * 522.5 / 2560, 1440 - 930));


	//设置地图选择按钮的监听
	Random->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音
		
		//设置按钮的点击后的持续效果
		Random->loadTextureNormal("customGameMenu/randomSelected.png");
		spacestation->loadTextureNormal("customGameMenu/spacestationUnselected.png");
		sunsetcity->loadTextureNormal("customGameMenu/sunsetcityUnselected.png");
		seele->loadTextureNormal("customGameMenu/seeleUnselected.png");
		irismood->loadTextureNormal("customGameMenu/irismoodUnselected.png");
		highmoon->loadTextureNormal("customGameMenu/highmoonUnselected.png");
		Default->loadTextureNormal("customGameMenu/defaultUnselected.png");

		//设置图片
		srand((unsigned)time(0));
		int num = rand() % 6;
		//std::vector<Button*>a = { spacestation ,sunsetcity,seele,irismood,highmoon,Default };
		switch (num) {
		case 0: {
			Sprite* pic0 = Sprite::create("customGameMenu/spacestationPreview.png");
			pic0->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
			this->addChild(pic0);
			break; }
		case 1: {
			Sprite* pic1 = Sprite::create("customGameMenu/sunsetcityPreview.png");
			pic1->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
			this->addChild(pic1);
			break; }
		case 2: {
			Sprite* pic2 = Sprite::create("customGameMenu/seelePreview.png");
			pic2->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
			this->addChild(pic2);
			break; }
		case 3: {
			/*auto pic3 = Sprite::create("customGameMenu/irismoodPreview.png");
			pic3->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
			this->addChild(pic3);*/
			break; }
		case 4: {
			/*auto pic4 = Sprite::create("customGameMenu/highmoonPreview.png");
			pic4->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
			this->addChild(pic4);*/
			break; }
		case 5: {
			Sprite* pic5 = Sprite::create("customGameMenu/defaultPreview.png");
			pic5->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
			this->addChild(pic5);
			break; }
		}
		GameManager::BackChoise = num;
		});

	spacestation->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音

		spacestation->loadTextureNormal("customGameMenu/spacestationSelected.png");
		Random->loadTextureNormal("customGameMenu/randomUnselected.png");
		sunsetcity->loadTextureNormal("customGameMenu/sunsetcityUnselected.png");
		seele->loadTextureNormal("customGameMenu/seeleUnselected.png");
		irismood->loadTextureNormal("customGameMenu/irismoodUnselected.png");
		highmoon->loadTextureNormal("customGameMenu/highmoonUnselected.png");
		Default->loadTextureNormal("customGameMenu/defaultUnselected.png");

		auto pic = Sprite::create("customGameMenu/spacestationPreview.png");
		pic->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
		this->addChild(pic);
		GameManager::BackChoise = 0;
		});

	sunsetcity->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音

		spacestation->loadTextureNormal("customGameMenu/spacestationUnselected.png");
		Random->loadTextureNormal("customGameMenu/randomUnselected.png");
		sunsetcity->loadTextureNormal("customGameMenu/sunsetcitySelected.png");
		seele->loadTextureNormal("customGameMenu/seeleUnselected.png");
		irismood->loadTextureNormal("customGameMenu/irismoodUnselected.png");
		highmoon->loadTextureNormal("customGameMenu/highmoonUnselected.png");
		Default->loadTextureNormal("customGameMenu/defaultUnselected.png");

		auto pic = Sprite::create("customGameMenu/sunsetcityPreview.png");
		pic->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
		this->addChild(pic);
		GameManager::BackChoise = 1;
		});
	seele->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音

		spacestation->loadTextureNormal("customGameMenu/spacestationUnselected.png");
		Random->loadTextureNormal("customGameMenu/randomUnselected.png");
		sunsetcity->loadTextureNormal("customGameMenu/sunsetcityUnselected.png");
		seele->loadTextureNormal("customGameMenu/seeleSelected.png");
		irismood->loadTextureNormal("customGameMenu/irismoodUnselected.png");
		highmoon->loadTextureNormal("customGameMenu/highmoonUnselected.png");
		Default->loadTextureNormal("customGameMenu/defaultUnselected.png");

		auto pic = Sprite::create("customGameMenu/seelePreview.png");
		pic->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
		this->addChild(pic);
		GameManager::BackChoise = 2;
		});
	irismood->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音

		spacestation->loadTextureNormal("customGameMenu/spacestationUnselected.png");
		Random->loadTextureNormal("customGameMenu/randomUnselected.png");
		sunsetcity->loadTextureNormal("customGameMenu/sunsetcityUnselected.png");
		seele->loadTextureNormal("customGameMenu/seeleUnselected.png");
		irismood->loadTextureNormal("customGameMenu/irismoodSelected.png");
		highmoon->loadTextureNormal("customGameMenu/highmoonUnselected.png");
		Default->loadTextureNormal("customGameMenu/defaultUnselected.png");

		/*auto pic = Sprite::create("customGameMenu/irismoodPreview.png");
		pic->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
		this->addChild(pic);*/
		GameManager::BackChoise = 3;
		});
	highmoon->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音

		spacestation->loadTextureNormal("customGameMenu/spacestationUnselected.png");
		Random->loadTextureNormal("customGameMenu/randomUnselected.png");
		sunsetcity->loadTextureNormal("customGameMenu/sunsetcityUnselected.png");
		seele->loadTextureNormal("customGameMenu/seeleUnselected.png");
		irismood->loadTextureNormal("customGameMenu/irismoodUnselected.png");
		highmoon->loadTextureNormal("customGameMenu/highmoonSelected.png");
		Default->loadTextureNormal("customGameMenu/defaultUnselected.png");

		/*auto pic = Sprite::create("customGameMenu/highmoonPreview.png");
		pic->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
		this->addChild(pic);*/
		GameManager::BackChoise = 4;
		});
	Default->addClickEventListener([=](Ref* sender) {
		//SimpleAudioEngine::getInstance()->playEffect("music/buttoneffect.mp3");//点击声音

		spacestation->loadTextureNormal("customGameMenu/spacestationUnselected.png");
		Random->loadTextureNormal("customGameMenu/randomUnselected.png");
		sunsetcity->loadTextureNormal("customGameMenu/sunsetcityUnselected.png");
		seele->loadTextureNormal("customGameMenu/seeleUnselected.png");
		irismood->loadTextureNormal("customGameMenu/irismoodUnselected.png");
		highmoon->loadTextureNormal("customGameMenu/highmoonUnselected.png");
		Default->loadTextureNormal("customGameMenu/defaultSelected.png");

		auto pic = Sprite::create("customGameMenu/defaultPreview.png");
		pic->setPosition(Vec2(origin.x + visibleSize.width * 1683 / 2560, 1440 - 735));
		this->addChild(pic);
		GameManager::BackChoise = 5;
		});



	this->addChild(Random);
	this->addChild(spacestation);
	this->addChild(sunsetcity);
	this->addChild(seele);
	this->addChild(irismood);
	this->addChild(highmoon);
	this->addChild(Default);
//===============================================\\地图选择部分结束//=================================================================



	////鼠标监听器//GameBegin的监听
	//blacksprite = Sprite::create("BlacktTransparent.png");
	////blacksprite->setAnchorPoint(Point(0, 0.5));
	//this->addChild(blacksprite, 7);
	//blacksprite->setVisible(false);

	//auto _mouseListener = EventListenerMouse::create();

	//_mouseListener->onMouseMove = CC_CALLBACK_1(BackgroundChoise::onMouseMove, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

}

void BackgroundChoise::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(StartScene::create());
		break;
	default:
		break;
	}
}

void BackgroundChoise::buttonCotinue(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//Director::getInstance()->replaceScene(StartScene::create());
		break;
	default:
		break;
	}
}

//
//void BackgroundChoise::onMouseMove(Event* event)
//{
//	EventMouse* e = (EventMouse*)event;
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY() + visibleSize.height));
//
//	Rect r = Rect(0, 0, getContentSize().width, getContentSize().height);
//
//	// Show selected image if mouse over
//	//r.containsPoint(locationInNode) ? selected() : unselected();
//}
//
//
//
////设置鼠标监听，用于滑条的显示。这里的鼠标监听类型为onMouseMove
//void BackgroundChoise::onMouseMove(Event* event)
//{
//	EventMouse* e = (EventMouse*)event;
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 locationInNode = convertToNodeSpace(Vec2(e->getCursorX(), e->getCursorY()));
//
//
//	Rect r1 = Rect(0, visibleSize.height * 3 / 5 - 50, visibleSize.width, 100);
//	Rect r2 = Rect(0, visibleSize.height * 3 / 5 - 250, visibleSize.width, 100);
//	Rect r3 = Rect(0, visibleSize.height * 3 / 5 - 450, visibleSize.width, 100);
//	CallFunc* setMove = CallFunc::create([&]() {
//		move = !move;
//		});
//
//	if (r1.containsPoint(locationInNode)) {
//		if (blacksprite->isVisible()) {
//			if (!move) {
//				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 3 / 5)));
//				auto seq = Sequence::create(setMove, move, setMove, nullptr);
//				seq->setTag(1);
//				blacksprite->stopActionByTag(1);
//				blacksprite->runAction(seq);
//			}
//		}
//		else {
//			blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5));
//			blacksprite->setVisible(true);
//			auto fadein = FadeIn::create(0.1);
//			blacksprite->runAction(fadein);
//		}
//	}
//	else if (r2.containsPoint(locationInNode)) {
//		if (blacksprite->isVisible()) {
//			if (!move) {
//				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 3 / 5 - 200)));
//				auto seq = Sequence::create(setMove, move, setMove, nullptr);
//				seq->setTag(1);
//				blacksprite->stopActionByTag(1);
//				blacksprite->runAction(seq);
//			}
//		}
//		else {
//			blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5 - 200));
//			blacksprite->setVisible(true);
//			auto fadein = FadeIn::create(0.1);
//			blacksprite->runAction(fadein);
//		}
//	}
//	else if (r3.containsPoint(locationInNode)) {
//		if (blacksprite->isVisible()) {
//			if (!move) {
//				auto move = EaseSineOut::create(MoveTo::create(0.08, Vec2(0, visibleSize.height * 3 / 5 - 400)));
//				auto seq = Sequence::create(setMove, move, setMove, nullptr);
//				seq->setTag(1);
//				blacksprite->stopActionByTag(1);
//				blacksprite->runAction(seq);
//			}
//		}
//		else {
//			blacksprite->setPosition(Vec2(0, visibleSize.height * 3 / 5 - 400));
//			blacksprite->setVisible(true);
//			auto fadein = FadeIn::create(0.1);
//			blacksprite->runAction(fadein);
//		}
//	}
//	else {
//		if (blacksprite->isVisible()) {
//			CallFunc* func1 = CallFunc::create([&]() {
//				blacksprite->setVisible(false);
//				});
//			auto fadeout = FadeOut::create(0.1f);
//			auto seq = Sequence::create(fadeout, func1, nullptr);
//			blacksprite->runAction(seq);
//		}
//	}
//}