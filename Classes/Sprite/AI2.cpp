#include "AI2.h"

AI2* AI2::create(int tag, MapBase* map)
{
    auto ai = new AI2();
    if (ai && ai->init(tag, map)) {
        ai->autorelease();
        return ai;
    }
    CC_SAFE_DELETE(ai);
    return nullptr;
}

bool AI2::init(int tag, MapBase* map)
{
    if (!AIBase::init(tag, map)) {
        return false;
    }

    status->acceleration = 1500;
    status->gravitation = -2757;
    status->resistance = 800;

    status->x_maxSpeed = 448;
    status->y_maxSpeed = 1275;
    status->recoil_speed = 100;

    //floor = map->Floor.size() - 1;

    /*unsigned seed = time(0);
    setPosition(rand() % int(map->platform->getContentSize().width / 2) + map->platform->getContentSize().width / 4,
        map->platform->getContentSize().height + 2000);*/

    return true;
}

void AI2::initBody()
{
    auto manager = UserManager::getInstance();

    std::string player_name;
    std::string face_name;
    std::string hat_name;

    /*if (this->getTag() == 1) {
        player_name = manager->player1_skin;
        face_name = manager->player1_face;
    }
    else {
        player_name = manager->player2_skin;
        face_name = manager->player2_face;
    }*/
    player_name = manager->player_skin[this->getTag()];
    face_name = manager->player_face[this->getTag()];
    hat_name = manager->player_hat[this->getTag()];

    //头和身体和帽子
    body = Body::CreateWithName(GameManager::Bodys[player_name]);
    organs.push_back(body);
    head = Head::CreateWithName(GameManager::Heads[player_name]);
    organs.push_back(head);
    hat = Hat::CreateWithName(GameManager::Hats[hat_name]);
    organs.push_back(hat);
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

    hat->setPosition(Vec2(0, 0));
    head->addChild(hat, 3);

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
    hand1->GetGun(gun, true);
    hand2->GetGun(gun, false);
    gun->player = this;

    AIBase::initBody();
}
