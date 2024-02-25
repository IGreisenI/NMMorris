#include "GameScene.h"
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

    _players.push_back(Player::create());
    _players.push_back(Player::create());

    auto playerInput = PlayerInput::create();
    auto turnController = TurnController::create(playerInput, _players);

    auto board = Board::create();

    for (int i = 0; i < 9; i++) {
        auto piece = Piece::create("Player1Piece.png");
        piece->setPosition(-270, -240 + piece->getChildren().at(0)->getBoundingBox().getMaxY() * 2 * i);
        piece->setOwner(_players.at(0));
        board->addChild(piece);
    }

    for (int i = 0; i < 9; i++) {
        auto piece = Piece::create("Player2Piece.png");
        piece->setPosition(270, -240 + piece->getChildren().at(0)->getBoundingBox().getMaxY() * 2 * i);
        piece->setOwner(_players.at(1));
        board->addChild(piece);
    }

    this->addChild(boardSprite);
    this->addChild(board);
    this->addChild(playerInput);
    this->addChild(turnController);

    for each (Player * player in _players) {
        this->addChild(player);
    }

    return true;
}
