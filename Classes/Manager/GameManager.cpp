#include "GameManager.h"

GameManager* GameManager::_instance;

std::map<std::string, EventKeyboard::KeyCode> GameManager::map1 = {
    {"up", EventKeyboard::KeyCode::KEY_W},
    {"down", EventKeyboard::KeyCode::KEY_S},
    {"left", EventKeyboard::KeyCode::KEY_A},
    {"right", EventKeyboard::KeyCode::KEY_D},
    {"shot", EventKeyboard::KeyCode::KEY_O },
    {"skill", EventKeyboard::KeyCode::KEY_P }
};
std::map<std::string, EventKeyboard::KeyCode> GameManager::map2 = {
    {"up", EventKeyboard::KeyCode::KEY_UP_ARROW},
    {"down", EventKeyboard::KeyCode::KEY_DOWN_ARROW},
    {"left", EventKeyboard::KeyCode::KEY_LEFT_ARROW},
    {"right", EventKeyboard::KeyCode::KEY_RIGHT_ARROW},
    {"shot", EventKeyboard::KeyCode::KEY_1 },
    {"skill", EventKeyboard::KeyCode::KEY_2 }
};

std::map<std::string, const char*> GameManager::Bodys = {
    {"Blue", "bodyBlue.png"},
    {"Pink", "bodyPink.png"},
    {"Purple", "bodyPurple.png"},
    {"Yellow", "bodyYello.png"},
    {"Black", "bodyBlack.png"},
    {"Green", "bodyGreen.png"},
    {"Red", "bodyRed.png"},
    {"White", "bodyWhite.png"}
};
std::map<std::string, const char*> GameManager::Heads = {
    {"Blue", "headBlue.png"},
    {"Pink", "headPink.png"},
    {"Purple", "headPurple.png"},
    {"Yellow", "headYello.png"},
    {"Black", "headBlack.png"},
    {"Green", "headGreen.png"},
    {"Red", "headRed.png"},
    {"White", "headWhite.png"}
};
std::map<std::string, const char*> GameManager::Hands = {
    {"Blue", "handBlue.png"},
    {"Pink", "handPink.png"},
    {"Purple", "handPurple.png"},
    {"Yellow", "handYello.png"},
    {"Black", "handBlack.png"},
    {"Green", "handGreen.png"},
    {"Red", "handRed.png"},
    {"White", "handWhite.png"}
};
std::map<std::string, const char*> GameManager::Feet = {
    {"Blue", "feetBlue.png"},
    {"Pink", "feetPink.png"},
    {"Purple", "feetPurple.png"},
    {"Yellow", "feetYello.png"},
    {"Black", "feetBlack.png"},
    {"Green", "feetGreen.png"},
    {"Red", "feetRed.png"},
    {"White", "feetWhite.png"}
};


std::map<std::string, const char*> GameManager::Faces = {
    {"Cross","cross.png"},
    {"Smile","smile.png"},
    {"Normal", "normal.png"},
    {"Dot", "dot.png"},
    {"Glass", "glass.png"}
};
std::map<std::string, const char*> GameManager::Hats = {
    {"Angel", "angel.png"},
    {"BlackHat", "blackhat.png"},
    {"Drop", "drop.png"},
    {"Tie", "tie.png" },
    {"WhiteHat", "whitehat.png"},
    {"None", nullptr}
};
std::map<std::string, const char*> GameManager::Costumes = {

};

int GameManager::BackChoise = 0;

std::vector<std::string> GameManager::BackChoises = {
    "spacestation","sunsetcity","seele","irismood","highmoon","default"
};

GameManager* GameManager::getInstance()
{
    if (_instance == NULL)
        _instance = new GameManager();
    return _instance;
}

float GameManager::Random(int min, int max) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(min, max);
    return distr(eng);
}

std::map<std::string, EventKeyboard::KeyCode> GameManager::getKeyMap(int name)
{
    if (name == 1)
        return map1;
    if (name == 2)
        return map2;
}
