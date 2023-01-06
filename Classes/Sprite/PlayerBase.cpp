#include "PlayerBase.h"

bool PlayerBase::initWithTag(int name, MapBase* map)
{
    if (!CharacterBase::init(name, map)) {
        return false;
    }

    keymap = GameManager::getKeyMap(name);
    
    initBody();

    initKeyboardListener();
    
    return true;
}

//PlayerBase* PlayerBase::createWithTag(int name, Sprite* background)
//{
//    auto player = new PlayerBase();
//    if (player && player->initWithTag(name, background)) {
//        player->autorelease();
//        return player;
//    }
//    CC_SAFE_DELETE(player);
//    return NULL;
//}

void PlayerBase::update(float dt)
{
    CharacterBase::update(dt);

}


void PlayerBase::initBody()
{
    hand1->setTag(1);
    hand2->setTag(2);
  
}


void PlayerBase::initKeyboardListener()
{
    EventListenerKeyboard* listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyPressed = CC_CALLBACK_2(PlayerBase::onKeyPressed, this);
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(PlayerBase::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
}


void PlayerBase::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == keymap["up"]) {
        keyMap["up"] = true;

    }
    if (keycode == keymap["down"]) {
        keyMap["down"] = true;

    }
    if (keycode == keymap["left"]) {
        keyMap["left"] = true;
        
    }
    if (keycode == keymap["right"]) {
        keyMap["right"] = true;
        
    }
    if (keycode == keymap["shot"]) {
        keyMap["shot"] = true;

    }
    if (keycode == keymap["skill"]) {
        keyMap["skill"] = true;
    }
}

void PlayerBase::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == keymap["left"]) {
        keyMap["left"] = false;
        
    }
    if (keycode == keymap["right"]) {
        keyMap["right"] = false;
        
    }
    if (keycode == keymap["up"]) {
        keyMap["up"] = false;
        keyMap["release"] = true;

    }
    if (keycode == keymap["shot"]) {
        keyMap["shot"] = false;

    }
    if (keycode == keymap["skill"]) {
        keyMap["skill"] = false;

    }
}
