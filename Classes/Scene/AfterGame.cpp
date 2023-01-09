#include"Scene/AfterGame.h"
#include"Scene/GameScene.h"
#include"Scene/PlayerSetup.h"
#include"Manager/UserManager.h"

Scene* AfterGame::createScene()
{
	return AfterGame::create();
}
bool AfterGame::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//创建背景
	auto background = Sprite::create("AfterGame/back.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//设置按钮
	auto Continue = ui::Button::create("AfterGame/continue.png", "AfterGame/continueON.png");
	Continue->setScale(1.0f);
	Continue->addTouchEventListener(CC_CALLBACK_2(AfterGame::buttonCallBack, this));
	Continue->setPosition(Vec2(origin.x + visibleSize.width * 1280/ 2560, origin.y + 1440 -1230));
	this->addChild(Continue);

	auto manager = UserManager::getInstance();
	std::string player1 = manager->player1;
	std::string player2 = manager->player2;
	auto map = manager->Standing;
	////测试
	map[player1] = { 100 ,0.75,7,6,4,420,300};
	////map[player1] = { 100,0.89,12,8,8,576,463 };
	map[player2] = { 100,0.89,12,8,8,576,463};

	//更新map
	map = calculate(player1,map);
	manager->Standing = calculate(player2, map);
	map = manager->Standing;

	auto vec1 = map[player1];
	auto vec2 = map[player2];
	//mark = 命中率 * 击杀数；生涯命中率；场均击杀；    总场数；该局击杀数；该局射击数; 该局命中数
	
	double hit_1 =vec1[6] ;
	double ts_1 = vec1[5];
	double acc_1 = hit_1/ts_1;
	double mark_1 = acc_1*vec1[4];
	double ctp_1 =vec1[0] ;
	double kpg_1 = vec1[2];
	double cacc_1 =vec1[1] ;

	double hit_2 = vec2[6];
	double ts_2 = vec2[5];
	double acc_2 = hit_2 / ts_2;
	double mark_2 = acc_2 * vec2[4];
	double ctp_2 = vec2[0];
	double kpg_2 = vec2[2];
	double cacc_2 = vec2[1];

	//布置页面
	double x1 = 361.5+20;
	double y1 =1440- 585-22;
	std::string mark1 = Dec_ToString(mark_1);
	auto Mark1 = Label::createWithTTF(mark1, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 100);
	Mark1->setTextColor(Color4B::BLACK);
	Mark1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Mark1->setPosition(Vec2(origin.x + visibleSize.width * 849 / 2560, 1440-491-22));
	this->addChild(Mark1);
	std::string hit1 = Dec_ToString(hit_1);
	auto Hit1 = Label::createWithTTF(hit1, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Hit1->setTextColor(Color4B::WHITE);
	Hit1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Hit1->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y1 ));
	this->addChild(Hit1);
	std::string ts1 = Dec_ToString(ts_1);
	auto Ts1 = Label::createWithTTF(ts1, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Ts1->setTextColor(Color4B::WHITE);
	Ts1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Ts1->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y1-100));
	this->addChild(Ts1);
	std::string acc1 = Dec_ToString(acc_1*100);
	acc1 = acc1 + "%";
	auto Acc1 = Label::createWithTTF(acc1, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Acc1->setTextColor(Color4B::WHITE);
	Acc1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Acc1->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y1 - 100*2));
	this->addChild(Acc1);
	std::string ctp1 = Dec_ToString(ctp_1);
	auto cTP1 = Label::createWithTTF(ctp1, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	cTP1->setTextColor(Color4B::WHITE);
	cTP1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cTP1->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y1 - 100 * 3));
	this->addChild(cTP1);
	std::string kpg1 = Dec_ToString(kpg_1);
	auto Kpg1 = Label::createWithTTF(kpg1, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Kpg1->setTextColor(Color4B::WHITE);
	Kpg1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Kpg1->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y1 - 100 * 4));
	this->addChild(Kpg1);
	std::string cacc1 = Dec_ToString(cacc_1 * 100);
	cacc1 = cacc1 + "%";
	auto Cacc1 = Label::createWithTTF(cacc1, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Cacc1->setTextColor(Color4B::WHITE);
	Cacc1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Cacc1->setPosition(Vec2(origin.x + visibleSize.width * x1 / 2560, y1 - 100 * 5));
	this->addChild(Cacc1);

	double x2 = 1531.5+20;
	double y2 = 1440 - 585 - 22;
	std::string mark2 = Dec_ToString(mark_2);
	auto Mark2 = Label::createWithTTF(mark2, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 100);
	Mark2->setTextColor(Color4B::BLACK);
	Mark2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Mark2->setPosition(Vec2(origin.x + visibleSize.width * 2018 / 2560, 1440 - 491 - 22));
	this->addChild(Mark2);
	std::string hit2 = Dec_ToString(hit_2);
	auto Hit2 = Label::createWithTTF(hit2, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Hit2->setTextColor(Color4B::WHITE);
	Hit2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Hit2->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y2));
	this->addChild(Hit2);
	std::string ts2 = Dec_ToString(ts_2);
	auto Ts2 = Label::createWithTTF(ts2, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Ts2->setTextColor(Color4B::WHITE);
	Ts2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Ts2->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y2 - 100));
	this->addChild(Ts2);
	std::string acc2 = Dec_ToString(acc_2 * 100);
	acc2 = acc2 + "%";
	auto Acc2 = Label::createWithTTF(acc2, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Acc2->setTextColor(Color4B::WHITE);
	Acc2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Acc2->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y2 - 100 * 2));
	this->addChild(Acc2);
	std::string ctp2 = Dec_ToString(ctp_2);
	auto cTP2 = Label::createWithTTF(ctp2, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	cTP2->setTextColor(Color4B::WHITE);
	cTP2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	cTP2->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y2 - 100 * 3));
	this->addChild(cTP2);
	std::string kpg2 = Dec_ToString(kpg_2);
	auto Kpg2 = Label::createWithTTF(kpg2, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Kpg2->setTextColor(Color4B::WHITE);
	Kpg2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Kpg2->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y2 - 100 * 4));
	this->addChild(Kpg2);
	std::string cacc2 = Dec_ToString(cacc_2 * 100);
	cacc2 = cacc2 + "%";
	auto Cacc2 = Label::createWithTTF(cacc2, "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
	Cacc2->setTextColor(Color4B::WHITE);
	Cacc2->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	Cacc2->setPosition(Vec2(origin.x + visibleSize.width * x2 / 2560, y2 - 100 * 5));
	this->addChild(Cacc2);



	//判断没有输入名字的情况
	if (player1 == "") {
		manager->Standing.erase("");
		manager->UserName.erase(find(manager->UserName.begin(), manager->UserName.end(), ""));
	}
	else if (player2 == "") {
		manager->Standing.erase("");
		manager->UserName.erase(find(manager->UserName.begin(), manager->UserName.end(), ""));
	}

	//写文件
	if(player1 == "" && player2 == ""){}//其实没必要,稍微快一点
	else{
		std::ofstream outClientFile("StandingFile.txt", std::ios::out);
		if (!outClientFile) {
			log("File Write ERROR");
			std::exit(EXIT_FAILURE);
		}
		std::map<std::string, std::vector<double>>::iterator it;
		for (it = manager->Standing.begin(); it != manager->Standing.end(); ++it) {
			outClientFile << it->first << " " << it->second[0] << " " << it->second[1] << " " << it->second[2] << " " << it->second[3] << " " << it->second[4] << " " << it->second[5] << " " << it->second[6] << std::endl;
		}
		outClientFile.close();
	}

	return true;
}

std::map<std::string, std::vector<double>> AfterGame::calculate(std::string s, std::map<std::string, std::vector<double>> &m) {
	//name;   mark=命中率*击杀数；生涯命中率；场均击杀；    总场数；该局击杀数；该局射击数;该局命中数
	m[s][3] += 1;//总场数；
	double num = m[s][3];
	double rate = m[s][6] / m[s][5];//该局命中率
	double mark = rate * m[s][4];
	m[s][0] += mark;//总分数
	m[s][1] = (m[s][1] * (num - 1) + rate) / num;//生涯命中率
	m[s][2] = (m[s][2] * (num - 1) + m[s][4]) / num;//场均击杀
	return m;
}

void AfterGame::buttonCallBack(Ref* ref, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type) {
	case Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(Transition::create(0.5f, PlayerSetup::create()));
		break;
	default:
		break;
	}
}

std::string AfterGame::Dec_ToString(double d) {
	double num = floor(d * 1000.0000f + 0.5) / 1000.0000f;
	std::ostringstream os;
	if (os << num)
		return os.str();
	return "invalid conversion";
}