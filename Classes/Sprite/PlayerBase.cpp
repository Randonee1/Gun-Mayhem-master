#include "PlayerBase.h"

bool PlayerBase::initWithTag(int name)
{
    if (!CharacterBase::init()) {
        return false;
    }

    this->setTag(name);

    keymap = GameManager::getKeyMap(name);

    initBody();

    initKeyboardListener();
    status->acceleration = 7000;
    status->gravitation = -8000 ;
    status->resistance = 1000;

    status->x_maxSpeed = 1300;
    status->y_maxSpeed = 3700;
    status->recoil_speed = 300;
    
    floor = 300;
    return true;
}

PlayerBase* PlayerBase::createWithTag(int name)
{
    auto player = new PlayerBase();
    if (player && player->initWithTag(name)) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

void PlayerBase::update(float dt)
{
    CharacterBase::update(dt);

}


void PlayerBase::initBody()
{
    //头和身体
    body = Body::CreateWithName("body_gameart/body.png");
    organs.push_back(body);
    head = Head::CreateWithName("body_gameart/head.png");
    organs.push_back(head);
    //四肢和脸
    face = Face::CreateWithName("body_gameart/face.png");
    organs.push_back(face);
    hand1 = Hand::CreateWithName("body_gameart/hand.png");
    organs.push_back(hand1);
    hand2 = Hand::CreateWithName("body_gameart/hand.png");
    organs.push_back(hand2);
    feet1 = Foot::CreateWithName("body_gameart/feet.png");
    organs.push_back(feet1);
    feet2 = Foot::CreateWithName("body_gameart/feet.png");
    organs.push_back(feet2);
    gun = GunBase::CreateWithName("body_gameart/gun_glock.png");
    
    head->setPosition(Vec2(36, 133));
    this->addChild(head, 1);

    hand1->setPosition(Vec2(-60, -58));
    this->addChild(hand1, 4);

    face->setPosition(Vec2(30, 0));
    head->addChild(face, 2);

    hand2->setPosition(Vec2(80, -32));
    this->addChild(hand2, -1);

    feet1->setPosition(Vec2(-96, -202));
    this->addChild(feet1, 3);

    feet2->setPosition(Vec2(4, -172));
    this->addChild(feet2, -1);

    body->setPosition(Vec2(-29, -3.5));
    this->addChild(body, 0);

    //gun->setPosition(Vec2(65, 30));
    hand1->GetGun(gun);
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
        keyMap["skill"];
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
}
