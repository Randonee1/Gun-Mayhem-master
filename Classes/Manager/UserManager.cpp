#include "Manager/UserManager.h"

UserManager* UserManager::_instance;

UserManager* UserManager::getInstance()
{
    if (_instance == NULL)
        _instance = new UserManager();
    return _instance;
}

std::vector<std::string> UserManager::UserName = {};

std::map<std::string, int> UserManager::User_marks = {};

std::string UserManager::player1="";

std::string UserManager::player2="";