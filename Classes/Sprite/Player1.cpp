#include "Player1.h"

Player1* Player1::createWithTag(int name, Sprite* background)
{
    auto player = new Player1();
    if (player && player->initWithTag(name, background)) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

bool Player1::initWithTag(int name, Sprite* background)
{
    if (!PlayerBase::initWithTag(name, background)) {
        return false;
    }

    status->acceleration = 2412;
    status->gravitation = -2757;
    status->resistance = 342;

    status->x_maxSpeed = 448;
    status->y_maxSpeed = 1275;
    status->recoil_speed = 100;

    floor_base = background->getContentSize().height + 30 - 270;
    floor_height = 270;
    Floor = { {0,1945},{270,1675} };
    floor = Floor.size()-1;

    setPosition(background->getContentSize().width / 2, background->getContentSize().height + 1500);
    initPosition = getPosition();

    return true;
}

void Player1::initBody()
{
    //头和身体
    body = Body::CreateWithName("Player1_body.png");
    organs.push_back(body);
    head = Head::CreateWithName("Player1_head.png");
    organs.push_back(head);
    //四肢和脸
    face = Face::CreateWithName("Player1_face.png");
    organs.push_back(face);
    hand1 = Hand::CreateWithName("Player1_hand.png");
    organs.push_back(hand1);
    hand2 = Hand::CreateWithName("Player1_hand.png");
    organs.push_back(hand2);
    feet1 = Foot::CreateWithName("Player1_foot.png");
    organs.push_back(feet1);
    feet2 = Foot::CreateWithName("Player1_foot.png");
    organs.push_back(feet2);
    gun = GunBase::CreateWithName("gun_test.png");

    head->setPosition(Vec2(65/2.2, 130/2.2));
    this->addChild(head, 1);

    hand1->setPosition(Vec2(-31/2.2, -55/2.2));
    this->addChild(hand1, 4);

    face->setPosition(Vec2(30/2.2, 0));
    head->addChild(face, 2);

    hand2->setPosition(Vec2(109/2.2, -29/2.2));
    this->addChild(hand2, -1);

    feet1->setPosition(Vec2(-67/2.2, -199/2.2));
    this->addChild(feet1, 3);

    feet2->setPosition(Vec2(33/2.2, -169/2.2));
    this->addChild(feet2, -1);

    body->setPosition(Vec2(0, 0));
    this->addChild(body, 0);

    //gun->setPosition(Vec2(65, 30));
    hand1->GetGun(gun);

}
