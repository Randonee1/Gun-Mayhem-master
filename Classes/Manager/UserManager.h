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

	std::string player1;

	std::string player2;

	//trueΪplayer, falseΪAI
	/*bool player1_type = false;

	bool player2_type = false;*/
	std::map<int, bool> player_type;

	/*std::string player1_skin = "White";

	std::string player2_skin = "White";*/
	std::map<int, std::string> player_skin;

	/*std::string player1_face = "Normal";

	std::string player2_face = "Normal";*/
	std::map<int, std::string> player_face;

	/*std::string player1_hat;

	std::string player2_hat;*/
	std::map<int, std::string> player_hat;

	int Live;
};

#endif
