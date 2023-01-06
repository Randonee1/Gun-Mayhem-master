#include"Scene/Standing.h"

#include <algorithm>
#include<vector>
#include<map>


std::string Standing::twoDec_ToString(double d) {
	double num = floor(d * 10.000000f + 0.5) / 10.000000f;
	std::ostringstream os;
	if (os << num)
		return os.str();
	return "invalid conversion";
}

bool Standing::cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
	return lhs.second[0] > rhs.second[0];
}

Scene* Standing::createScene()
{
	return Standing::create();
}
bool Standing::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//创建背景
	auto background = Sprite::create("ranking/ranking.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//设置按钮
	auto BackToMenuButton = ui::Button::create("ranking/backon.png", "ranking/back.png");
	BackToMenuButton->setScale(1.0f);
	BackToMenuButton->addTouchEventListener(CC_CALLBACK_2(Standing::buttonCallBack, this));
	BackToMenuButton->setPosition(Vec2(origin.x + visibleSize.width * (775.5-70+1160) / 2560, origin.y + 1440 - 420-198*4));
	this->addChild(BackToMenuButton);

	//对Standing排序
	auto manager = UserManager::getInstance();
	std::map<std::string,std::vector<double>> map = manager->Standing;
	std::vector<PAIR> vec(map.begin(), map.end());
	sort(vec.begin(), vec.end(), cmp_by_value);

	for (int i = 0; i < vec.size(); ++i) {
		auto name = Label::createWithTTF(vec[i].first, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
		name->setTextColor(Color4B::BLACK);
		name->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		
		std::string sacc = twoDec_ToString(vec[i].second[1]);
		sacc = sacc + "%";
		auto acc = Label::createWithTTF(sacc, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
		acc->setTextColor(Color4B::BLACK);
		acc->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		
		std::string skpg = twoDec_ToString(vec[i].second[2]);
		auto kpg = Label::createWithTTF(skpg, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
		kpg->setTextColor(Color4B::BLACK);
		kpg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		
		std::string sctp = twoDec_ToString(vec[i].second[0]);
		auto ctp = Label::createWithTTF(sctp, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed Bold.ttf", 72);
		ctp->setTextColor(Color4B::BLACK);
		ctp->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		int y = 1440-456-17;
		int x1 = 295.5;
		int x2 = 565.5;
		int x3 = 775.5;
		int x4 = 985.5;
		switch (i) {
		case 0: {
			
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560,y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
		case 1: {
			y = y - 198;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
		case 2: {
			y -= 198 * 2;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
		case 3: {
			y -= 198 * 3;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
		case 4: {
			y -= 198 * 4;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
		case 5: {
			x1 += 1160;
			x2 += 1160;
			x3 += 1160;
			x4 += 1160;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;

		}
		case 6: {
			x1 += 1160;
			x2 += 1160;
			x3 += 1160;
			x4 += 1160;
			y -= 198;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
		case 7: {
			x1 += 1160;
			x2 += 1160;
			x3 += 1160;
			x4 += 1160;
			y -= 198*2;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
		case 8: {
			x1 += 1160;
			x2 += 1160;
			x3 += 1160;
			x4 += 1160;
			y -= 198*3;
			name->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y));
			this->addChild(name);
			acc->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y));
			this->addChild(acc);
			kpg->setPosition(Vec2(origin.x + visibleSize.width * x3 / 2560, y));
			this->addChild(kpg);
			ctp->setPosition(Vec2(origin.x + visibleSize.width * x4 / 2560, y));
			this->addChild(ctp);
			break;
		}
			
		}
	}
	return true;
}
void Standing::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(Transition::create(0.5f, StartScene::create()));
		break;
	default:
		break;
	}
}