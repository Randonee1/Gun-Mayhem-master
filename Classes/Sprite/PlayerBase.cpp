#include "PlayerBase.h"
#include "Manager/GameManager.h"

bool PlayerBase::initWithTag(int name)
{
    if (!Sprite::init()) {
        return false;
    }
    this->name = name;
    this->setTag(name);

    keymap = GameManager::getKeyMap(name);

    initBody();

    initKeyboardListener();
    acceleration = 7000;
    gravitation = -8000 ;
    accelerate = 0;
    x_speed = 0;
    x_speed = 0;
    x_maxSpeed = 1300;
    y_maxSpeed = 3700;
    recoil_speed = 300;
    isDoubleJump = false;
    inTheAir = false;
    floor = 5000;
    this->scheduleUpdate();
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
    Node::update(dt);
    //CCLOG("%f", getPositionY());

    if (!inTheAir) {
        isDoubleJump = false;
        if (keyMap[keymap["up"]]) {
            inTheAir = true;
            y_speed = y_maxSpeed;
            MoveDelay(true,false);
            keyMap[keymap["up"]] = false;
        }
        else
            y_speed = 0;
    }
    else {
        //跳起暂停走路动作
        feet1->organ->stopActionByTag(10);
        feet2->organ->stopActionByTag(10);
        feet1->actionState = false;
        feet2->actionState = false;
        hand1->organ->stopActionByTag(10);
        hand2->organ->stopActionByTag(10);
        hand1->actionState = false;
        hand2->actionState = false;

        if (std::abs(y_speed) <= std::abs(gravitation * dt))
            MoveDelay(false, false);
        if (!isDoubleJump && keyMap[keymap["up"]]) {
            y_speed = y_maxSpeed/1.2;
            MoveDelay(true,false);
            isDoubleJump = true;
        }
        y_speed += gravitation * dt;
        keyMap[keymap["up"]] = false;
    }
    if (getPositionY() + y_speed * dt < floor) {
        MoveDelay(true, true);
        inTheAir = false;
        y_speed = 0;

        this->setPositionY(floor);
    }else
        this->setPositionY(getPositionY() + y_speed * dt);


    if ((keyMap[keymap["left"]] ^ keyMap[keymap["right"]])) {

        accelerate = keyMap[keymap["right"]] ? Right() : Left();
        if(!inTheAir){

            feet1->GoRight();
            feet2->GoLeft();
            hand2->GoRight();
            hand1->GoLeft();

        }
        x_speed += accelerate * dt;
        if (std::abs(x_speed) > x_maxSpeed)
            x_speed -= accelerate * dt;
    }
    else {
        accelerate = x_speed > 0 ? Left()/7 : Right()/7;
        if (std::abs(accelerate * dt) > std::abs(x_speed))
            x_speed = 0;
        else
            x_speed += accelerate * dt;
    }
    this->setPositionX(getPositionX() + x_speed * dt);

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

float PlayerBase::Right()
{
    return acceleration;
}

float PlayerBase::Left()
{
    return -acceleration;
}

void PlayerBase::Flip(bool direction)
{
    this->setFlippedX(direction);
    for (auto organ : organs)
        organ->setFlippedX(direction);
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
        //CCLOG("jump");
        keyMap[keycode] = true;
    }
    if (keycode == keymap["down"]) {
        //CCLOG("down");
    }
    if (keycode == keymap["left"]) {
        //CCLOG("left");
        keyMap[keycode] = true;
        //feet1->stopAllActions();
        //feet1->actionState = false;
        Flip(true);
    }
    if (keycode == keymap["right"]) {
        //CCLOG("right");
        keyMap[keycode] = true;
        //feet1->stopAllActions();
        //feet1->actionState = false;
        Flip(false);
    }
    if (keycode == keymap["shot"]) {
        hand1->RaiseHandToShoot(this->getParent());
        this->_flippedX ? x_speed += recoil_speed : x_speed -= recoil_speed;
        if (std::abs(x_speed) > x_maxSpeed)
            this->_flippedX ? x_speed = x_maxSpeed : x_speed = -x_maxSpeed;
    }
}

void PlayerBase::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == keymap["left"]) {
        //CCLOG("left end");
        keyMap[keycode] = false;
        if (keyMap[keymap["right"]])
            Flip(false);
    }
    if (keycode == keymap["right"]) {
        //CCLOG("right end");
        keyMap[keycode] = false;
        if (keyMap[keymap["left"]])
            Flip(true);
    }
}

void PlayerBase::MoveDelay(bool up,bool floor)
{
    for (int i = 2; i < organs.size(); i++)
        organs[i]->MoveDelay(up, floor);
}
