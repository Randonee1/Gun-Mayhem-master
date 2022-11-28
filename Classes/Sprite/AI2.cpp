#include "AI2.h"

AI2* AI2::create(MapBase* map)
{
    auto ai = new AI2();
    if (ai && ai->init(map)) {
        ai->autorelease();
        return ai;
    }
    CC_SAFE_DELETE(ai);
    return nullptr;
}

bool AI2::init(MapBase* map)
{
    if (!AIBase::init(map)) {
        return false;
    }

    status->acceleration = 1500;
    status->gravitation = -2757;
    status->resistance = 800;

    status->x_maxSpeed = 448;
    status->y_maxSpeed = 1275;
    status->recoil_speed = 100;

    floor = map->Floor.size() - 1;

    unsigned seed = time(0);
    setPosition(rand() % int(map->platform->getContentSize().width / 2) + map->platform->getContentSize().width / 4,
        map->platform->getContentSize().height + 2000);

    return true;
}

void AI2::initBody()
{
    std::string player_name;
    unsigned seed = time(0);
    srand(seed);
    switch (rand() % 4) {
    case 0:
        player_name = "Blue";
        break;
    case 1:
        player_name = "Pink";
        break;
    case 2:
        player_name = "Purple";
        break;
    case 3:
        player_name = "Yellow";
        break;
    }
    std::string face_name = "Cross";
    //ͷ������
    body = Body::CreateWithName(GameManager::Bodys[player_name]);
    organs.push_back(body);
    head = Head::CreateWithName(GameManager::Heads[player_name]);
    organs.push_back(head);
    //��֫����
    face = Face::CreateWithName(GameManager::Faces[face_name]);
    organs.push_back(face);
    hand1 = Hand::CreateWithName(GameManager::Hands[player_name]);
    organs.push_back(hand1);
    hand2 = Hand::CreateWithName(GameManager::Hands[player_name]);
    organs.push_back(hand2);
    feet1 = Foot::CreateWithName(GameManager::Feet[player_name]);
    organs.push_back(feet1);
    feet2 = Foot::CreateWithName(GameManager::Feet[player_name]);
    organs.push_back(feet2);

    initGun = Gun_Glock::create();

    gun = Gun_Glock::create();

    head->setPosition(Vec2(65 / 2.2 - 8, 130 / 2.2 - 2));
    this->addChild(head, 1);

    hand1->initPosition = Vec2(-31 / 2.2, -55 / 2.2);
    hand1->setPosition(hand1->initPosition);
    this->addChild(hand1, 4);

    face->setPosition(Vec2(30 / 2.2, 0));
    head->addChild(face, 2);

    hand2->initPosition = Vec2(109 / 2.2, -29 / 2.2);
    hand2->setPosition(hand2->initPosition);
    this->addChild(hand2, -1);

    feet1->setPosition(Vec2(-67 / 2.2, -199 / 2.2));
    this->addChild(feet1, 3);

    feet2->setPosition(Vec2(33 / 2.2, -169 / 2.2));
    this->addChild(feet2, -1);

    body->setPosition(Vec2(0, 0));
    this->addChild(body, 0);

    //gun->setPosition(Vec2(65, 30));
    hand1->GetGun(gun);
}