#include "Manager/UserManager.h"

UserManager* UserManager::_instance;

UserManager::UserManager()
{
    player_type[1] = false;
    player_type[2] = false;
    player_name[1] = "player1";
    player_name[2] = "player2";
    player_face[1] = "Normal";
    player_face[2] = "Normal";
    player_skin[1] = "White";
    player_skin[2] = "White";
    player_hat[1] = "None";
    player_hat[2] = "None";
    Live = 10000;
}

UserManager* UserManager::getInstance()
{
    if (_instance == NULL)
        _instance = new UserManager();
    return _instance;
}

std::string UserManager::SkinRandom()
{
    std::string skin;
    switch (rand() % 8) {
    case 0:
        skin = "Blue";
        break;
    case 1:
        skin = "Pink";
        break;
    case 2:
        skin = "Purple";
        break;
    case 3:
        skin = "Yellow";
        break;
    case 4:
        skin = "Black";
        break;
    case 5:
        skin = "Green";
        break;
    case 6:
        skin = "Red";
        break;
    case 7:
        skin = "White";
        break;
    }
    return skin;
}

std::string UserManager::FaceRandom()
{
    std::string face;

    switch (rand() % 5) {
    case 0:
        face = "Cross";
        break;
    case 1:
        face = "Smile";
        break;
    case 2:
        face = "Normal";
        break;
    case 3: 
        face = "Dot";
        break;
    case 4:
        face = "Glass";
        break;
    }

    return face;
}

std::string UserManager::HatRandom()
{
    std::string hat;

    switch (rand() % 6) {
    case 0:
        hat = "Angel";
        break;
    case 1:
        hat = "BlackHat";
        break;
    case 2:
        hat = "Drop";
        break;
    case 3:
        hat = "Tie";
        break;
    case 4:
        hat = "WhiteHat";
        break;
    case 5: 
        hat = "None";
        break;
    }

    return hat;
}

//std::vector<std::string> UserManager::UserName = {};
//
//std::map<std::string, int> UserManager::User_marks = {};
//
//std::string UserManager::player1="";
//
//std::string UserManager::player2="";