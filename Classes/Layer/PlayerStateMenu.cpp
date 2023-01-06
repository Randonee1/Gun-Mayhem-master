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

    boardPlayer1 = Sprite::create("board_player1.png");
    boardPlayer1->setAnchorPoint(Vec2(0.5, 0));
    boardPlayer1->setPosition(1000, -boardPlayer1->getContentSize().height);
    this->addChild(boardPlayer1);

    boardBack1 = Sprite::create("board_back.png");
    boardBack1->setPosition(boardBack1->getContentSize().width / 2, boardBack1->getContentSize().height / 2);
    boardPlayer1->addChild(boardBack1, -1);

    auto player1 = CreateAvatar(1);
    player1->setPosition(322, 17);
    boardBack1->addChild(player1, 1);

    livePlayer1 = Label::createWithTTF(std::to_string(UserManager::getInstance()->Live), "fonts/gill-sans-mt-condensed/Gill Sans MT Condensed.TTF", 72);
    livePlayer1->setTextColor(Color4B::BLACK);
    livePlayer1->setAnchorPoint(Vec2(0.5, 0.5));


    boardPlayer2 = Sprite::create("board_player2.png");
    boardPlayer2->setAnchorPoint(Vec2(0.5, 0));
    boardPlayer2->setPosition(visibleSize.x - 1000, -boardPlayer2->getContentSize().height);
    this->addChild(boardPlayer2);

    boardBack2 = Sprite::create("board_back.png");
    boardBack2->setPosition(boardBack2->getContentSize().width / 2, boardBack2->getContentSize().height / 2);
    boardPlayer2->addChild(boardBack2, -1);

    auto player2 = CreateAvatar(2);
    player2->setPosition(322, 17);
    boardBack2->addChild(player2, 1);
    

    return true;
}

void PlayerStateMenu::bindMap(MapBase* map)
{
    this->map = map;
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
    auto move = MoveBy::create(0.3, Vec2(0, boardPlayer1->getContentSize().height));
    auto seq = Sequence::create(delay, move, nullptr);
    boardPlayer1->runAction(seq->clone());
    boardPlayer2->runAction(seq->clone());
}
