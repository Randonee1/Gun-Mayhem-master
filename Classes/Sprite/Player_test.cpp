#include "Player_test.h"

Player_test* Player_test::createWithTag(int name, MapBase* map)
{
    auto player = new Player_test();
    if (player && player->initWithTag(name, map)) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

bool Player_test::initWithTag(int name, MapBase* map)
{
    if (!PlayerBase::initWithTag(name, map)) {
        return false;
    }

    status->acceleration = 7000;
    status->gravitation = -8000;
    status->resistance = 1000;

    status->x_maxSpeed = 1300;
    status->y_maxSpeed = 3700;
    status->recoil_speed = 300;

    floor = 300;

    return true;
}

void Player_test::initBody()
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
    //gun = GunBase::CreateWithName("body_gameart/gun_glock.png");

    head->setPosition(Vec2(65, 130));
    this->addChild(head, 1);

    hand1->setPosition(Vec2(-31, -55));
    this->addChild(hand1, 4);

    face->setPosition(Vec2(30, 0));
    head->addChild(face, 2);

    hand2->setPosition(Vec2(109, -29));
    this->addChild(hand2, -1);

    feet1->setPosition(Vec2(-67, -199));
    this->addChild(feet1, 3);

    feet2->setPosition(Vec2(33, -169));
    this->addChild(feet2, -1);

    body->setPosition(Vec2(0, 0));
    this->addChild(body, 0);

    //gun->setPosition(Vec2(65, 30));
    hand1->GetGun(gun);
}
