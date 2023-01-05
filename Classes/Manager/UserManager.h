#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "cocos2d.h"
#include<vector>
#include<map>
USING_NS_CC;

class UserManager
{
public:
	static UserManager* getInstance();
	static UserManager* _instance;
	static std::vector<std::string> UserName;
	static std::map<std::string, int> User_marks;
	static std::string player1;
	static std::string player2;

};

#endif
