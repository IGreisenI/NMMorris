#include "GameScene.h"
#include "Board.h"
#include "Player.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = GameScene::create();
    scene->addChild(layer);

    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto windowSize = Director::getInstance()->getWinSizeInPixels();
    auto boardSprite = Sprite::create("Background.png");
    boardSprite->setPosition(windowSize.width / 2, windowSize.height / 2);


    auto player1 = Player::create();

    auto board = Board::create();

    for (int i = 0; i < 9; i++) {
        auto piece = Piece::create("Player1Piece.png");
        piece->setPosition(-270, -240 + piece->getChildren().at(0)->getBoundingBox().getMaxY() * 2 * i);
        board->addChild(piece);
    }

    for (int i = 0; i < 9; i++) {
        auto piece = Piece::create("Player2Piece.png");
        piece->setPosition(270, -240 + piece->getChildren().at(0)->getBoundingBox().getMaxY() * 2 * i);
        board->addChild(piece);
    }

    this->addChild(boardSprite);
    this->addChild(board);
    this->addChild(player1);

    return true;
}
