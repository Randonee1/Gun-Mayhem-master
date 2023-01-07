#include "PlayerStateMenu.h"
#include "Manager/UserManager.h"
#include "Map/MapBase.h"

bool PlayerStateMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Vec2 visibleSize = Director::getInstance()->getVisibleSize();

    boardPlayer[1] = Sprite::create("board_player1.png");
    boardPlayer[1]->setAnchorPoint(Vec2(0.5, 0));
    boardPlayer[1]->setPosition(1000, -boardPlayer[1]->getContentSize().height);
    this->addChild(boardPlayer[1]);

    boardBack[1] = Sprite::create("board_back.png");
    boardBack[1]->setPosition(boardBack[1]->getContentSize().width / 2, boardBack[1]->getContentSize().height / 2);
    boardPlayer[1]->addChild(boardBack[1], -1);

    auto player1 = CreateAvatar(1);
    player1->setPosition(322, 17);
    boardBack[1]->addChild(player1, 1);

    livePlayer[1] = Label::createWithTTF(std::to_string(UserManager::getInstance()->Live), "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed Bold.TTF", 60);
    livePlayer[1]->setTextColor(Color4B(170, 0, 0, 255));
    livePlayer[1]->setAnchorPoint(Vec2(0, 0.5));
    livePlayer[1]->setPosition(110, 90);
    boardPlayer[1]->addChild(livePlayer[1], 1);

    ammoPlayer[1] = Label::createWithTTF("0", "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed Bold.TTF", 48);
    ammoPlayer[1]->setTextColor(Color4B(255, 128, 0, 255));
    ammoPlayer[1]->setAnchorPoint(Vec2(0, 0.5));
    ammoPlayer[1]->setPosition(110, 40);
    boardPlayer[1]->addChild(ammoPlayer[1], 1);


    boardPlayer[2] = Sprite::create("board_player2.png");
    boardPlayer[2]->setAnchorPoint(Vec2(0.5, 0));
    boardPlayer[2]->setPosition(visibleSize.x - 1000, -boardPlayer[2]->getContentSize().height);
    this->addChild(boardPlayer[2]);

    boardBack[2] = Sprite::create("board_back.png");
    boardBack[2]->setPosition(boardBack[2]->getContentSize().width / 2, boardBack[2]->getContentSize().height / 2);
    boardPlayer[2]->addChild(boardBack[2], -1);

    auto player2 = CreateAvatar(2);
    player2->setPosition(322, 17);
    boardBack[2]->addChild(player2, 1);

    livePlayer[2] = Label::createWithTTF(std::to_string(UserManager::getInstance()->Live), "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed Bold.TTF", 60);
    livePlayer[2]->setTextColor(Color4B(170, 0, 0, 255));
    livePlayer[2]->setAnchorPoint(Vec2(0, 0.5));
    livePlayer[2]->setPosition(110, 90);
    boardPlayer[2]->addChild(livePlayer[2], 1);

    ammoPlayer[2] = Label::createWithTTF("0", "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed Bold.TTF", 48);
    ammoPlayer[2]->setTextColor(Color4B(255, 128, 0, 255));
    ammoPlayer[2]->setAnchorPoint(Vec2(0, 0.5));
    ammoPlayer[2]->setPosition(110, 40);
    boardPlayer[2]->addChild(ammoPlayer[2], 1);
    

    return true;
}

void PlayerStateMenu::bindMap(MapBase* map)
{
    this->map = map;
}

void PlayerStateMenu::SetLive(int live, int tag)
{
    std::string Live = std::to_string(live);
    livePlayer[tag]->setString(Live);
}

void PlayerStateMenu::SetAmmo(int ammo, int tag)
{
    if (ammo < 0)ammo = 0;
    std::string Ammo = std::to_string(ammo);
    if (ammo == INT_MAX)Ammo = "00";
    ammoPlayer[tag]->setString(Ammo);
}

Sprite* PlayerStateMenu::CreateAvatar(int tag)
{
	Sprite* player = new Sprite();

	auto manager = UserManager::getInstance();

	Sprite* body = Sprite::createWithSpriteFrameName(GameManager::Bodys[manager->player_skin[tag]]);
	Sprite* head = Sprite::createWithSpriteFrameName(GameManager::Heads[manager->player_skin[tag]]);
	Sprite* face = Sprite::createWithSpriteFrameName(GameManager::Faces[manager->player_face[tag]]);
	Sprite* hat = GameManager::Hats[manager->player_hat[tag]] ?
		Sprite::createWithSpriteFrameName(GameManager::Hats[manager->player_hat[tag]]) : new Sprite();

    body->setFlippedX(true);
    head->setFlippedX(true);
    face->setFlippedX(true);
    hat->setFlippedX(true);

    Vec2 anchor = face->getAnchorPoint();
    anchor.x = 1 - anchor.x;
    face->setAnchorPoint(anchor);

    head->setPosition(Vec2(-(65 / 2.2 - 8), 130 / 2.2 - 2));
	player->addChild(head, 1);

	hat->setPosition(Vec2(0, 0) + head->getContentSize() / 2);
	head->addChild(hat, 3);

	face->setPosition(Vec2(-30 / 2.2, 0) + head->getContentSize() / 2);
	head->addChild(face, 2);

	body->setPosition(Vec2(0, 0));
	player->addChild(body, 0);

    player->setScale(1.2);

    return player;
}

void PlayerStateMenu::onEnterTransitionDidFinish()
{
    auto delay = DelayTime::create(1.2);
    auto move = MoveBy::create(0.3, Vec2(0, boardPlayer[1]->getContentSize().height));
    auto seq = Sequence::create(delay, move, nullptr);
    boardPlayer[1]->runAction(seq->clone());
    boardPlayer[2]->runAction(seq->clone());
}
