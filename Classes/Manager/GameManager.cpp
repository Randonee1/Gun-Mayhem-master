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

GameManager* GameManager::getInstance()
{
    if (_instance == NULL)
        _instance = new GameManager();
    return _instance;
}

std::map<std::string, EventKeyboard::KeyCode> GameManager::getKeyMap(int name)
{
    if (name == 1)
        return map1;
    if (name == 2)
        return map2;
}
