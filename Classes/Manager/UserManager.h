#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "cocos2d.h"
#include<vector>
#include<map>
USING_NS_CC;

class UserManager
{
public:
	UserManager();

	static UserManager* getInstance();

	static UserManager* _instance;

	std::string SkinRandom();

	std::string FaceRandom();

	std::string HatRandom();

	std::vector<std::string> UserName;

	std::map<std::string, int> User_marks;

	std::map<std::string, std::vector<double>>Standing;//name;   mark=命中率*击杀数；生涯命中率；场均击杀；    总场数；该局击杀数；该局射击数;该局命中数

	//std::string player1;

	//std::string player2;



	std::map<int, std::string> player_name;

	std::map<int, bool> player_type;

	std::map<int, std::string> player_skin;

	std::map<int, std::string> player_face;

	std::map<int, std::string> player_hat;

	int Live;
};

#endif
