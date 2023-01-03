#include "PlayerStateMenu.h"

bool PlayerStateMenu::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Vec2 visibleSize = Director::getInstance()->getVisibleSize();

    boardPlayer1 = Sprite::create("board_player1.png");
    boardBack1 = Sprite::create("board_back.png");
    boardPlayer1->setAnchorPoint(Vec2(0.5, 0));
    boardPlayer1->setPosition(1000, 0);
    boardBack1->setPosition(boardBack1->getContentSize().width / 2, boardBack1->getContentSize().height / 2);
    boardPlayer1->addChild(boardBack1, -1);
    this->addChild(boardPlayer1);

    boardPlayer2 = Sprite::create("board_player2.png");
    boardBack2 = Sprite::create("board_back.png");
    boardPlayer2->setAnchorPoint(Vec2(0.5, 0));
    boardPlayer2->setPosition(visibleSize.x - 1000, 0);
    boardBack2->setPosition(boardBack2->getContentSize().width / 2, boardBack2->getContentSize().height / 2);
    boardPlayer2->addChild(boardBack2, -1);
    this->addChild(boardPlayer2);

    return true;
}
