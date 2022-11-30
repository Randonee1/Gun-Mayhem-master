#include "Player2.h"
#include "Skill/SpeedUp.h"

Player2* Player2::createWithTag(int name, MapBase* map)
{
    auto player = new Player2();
    if (player && player->initWithTag(name, map)) {
        player->autorelease();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

bool Player2::initWithTag(int name, MapBase* map)
{
    if (!PlayerBase::initWithTag(name, map)) {
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

void Player2::initBody()
{
    std::string player_name = "Pink";
    std::string face_name = "Normal1";
    //头和身体
    body = Body::CreateWithName(GameManager::Bodys[player_name]);
    organs.push_back(body);
    head = Head::CreateWithName(GameManager::Heads[player_name]);
    organs.push_back(head);
    //四肢和脸
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
