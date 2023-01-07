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
	auto background = Sprite::create("ranking/ranking.png");
	background->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	background->setPosition(origin.x, origin.y);
	auto contentSize = background->getContentSize();
	background->setScale(visibleSize.width / contentSize.width, visibleSize.height / contentSize.height);
	this->addChild(background);

	//设置按钮
	auto Continue = ui::Button::create("ranking/backon.png", "ranking/back.png");
	Continue->setScale(1.0f);
	Continue->addTouchEventListener(CC_CALLBACK_2(AfterGame::buttonCallBack, this));
	Continue->setPosition(Vec2(origin.x + visibleSize.width * (775.5 - 70 + 1160) / 2560, origin.y + 1440 - 420 - 198 * 4));
	this->addChild(Continue);

	auto manager = UserManager::getInstance();
	std::string player1 = manager->player1;
	std::string player2 = manager->player2;
	auto map = manager->Standing;
	//测试
	map[player1] = { 100 ,0.75,7,6,4,420,300};
	//map[player1] = { 100,0.89,12,8,8,576,463 };
	map[player2] = { 100,0.89,12,8,8,576,463};

	//更新map
	map = calculate(player1,map);
	manager->Standing = calculate(player2, map);
	
	//布置页面


	//判断没有输入名字的情况
	if (player1 == "") {
		manager->Standing.erase("");
	}
	else if (player2 == "") {
		manager->Standing.erase("");
	}

	//写文件
	std::ofstream outClientFile("StandingFile.txt", std::ios::out);
	if (!outClientFile) {
		log("File Write ERROR");
		std::exit(EXIT_FAILURE);
	}
	std::map<std::string, std::vector<double>>::iterator it;
	for (it = manager->Standing.begin(); it != manager->Standing.end();++it) {
		outClientFile << it->first << " " << it->second[0] << " " << it->second[1] << " " << it->second[2] << " " << it->second[3] << " " << it->second[4] << " " << it->second[5] <<" "<<it->second[6]<< std::endl;
	}
	outClientFile.close();

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