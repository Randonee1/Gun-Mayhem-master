#include "AnimationManager.h"

AnimationManager* AnimationManager::_instance;

AnimationManager* AnimationManager::getInstance()
{
    if (_instance == NULL)
        _instance = new AnimationManager();
    return _instance;
}
