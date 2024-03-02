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

    setupEventListeners();

    auto windowSize = Director::getInstance()->getWinSizeInPixels();
    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setPosition(windowSize.width / 2, windowSize.height / 2);

    _players.push_back(Player::create("Steve"));
    _players.push_back(Player::create("The Old One - World Destroyer"));

    auto checker = Checker::create(_players);
    auto playerInput = PlayerInput::create(_players, checker);
    auto turnController = TurnController::create(playerInput, _players);
    auto stageController = StageController::create();

    auto board = Board::create("board.png");

    for (int i = 0; i < 9; i++) {
        auto piece = Piece::create("Player1PieceV2.png", "Player1PieceV2Selected.png");
        board->addChild(piece);
        piece->setPosition(board->getBoundingBoxOfSprite().getMinX() + piece->getPieceSprite()->getBoundingBox().getMinX() - 4, board->getBoundingBoxOfSprite().getMinY() + piece->getChildren().at(0)->getBoundingBox().getMaxY() + piece->getChildren().at(0)->getBoundingBox().getMaxY() * 2 * i);
        _players.at(0)->addPieceToPlayer(piece);
    }
    auto player1Label = Label::createWithTTF(_players.at(0)->getName(), "fonts/arial.ttf", 20);
    board->addChild(player1Label);
    player1Label->setAnchorPoint(Vec2(0,1));
    player1Label->setPosition(board->getBoundingBoxOfSprite().getMinX(), board->getBoundingBoxOfSprite().getMinY());


    for (int i = 0; i < 9; i++) {
        auto piece = Piece::create("Player2PieceV2.png", "Player2PieceV2Selected.png");
        board->addChild(piece);
        piece->setPosition(board->getBoundingBoxOfSprite().getMaxX() + piece->getPieceSprite()->getBoundingBox().getMaxX() + 4, board->getBoundingBoxOfSprite().getMinY() + piece->getChildren().at(0)->getBoundingBox().getMaxY() + piece->getChildren().at(0)->getBoundingBox().getMaxY() * 2 * i);
        _players.at(1)->addPieceToPlayer(piece);
    }
    auto player2Label = Label::createWithTTF(_players.at(1)->getName(), "fonts/arial.ttf", 20);
    board->addChild(player2Label);
    player2Label->setAnchorPoint(Vec2(1, 1));
    player2Label->setPosition(board->getBoundingBoxOfSprite().getMaxX(), board->getBoundingBoxOfSprite().getMinY());

    this->addChild(backgroundSprite);
    this->addChild(board);
    this->addChild(playerInput);
    this->addChild(turnController);
    this->addChild(stageController);
    this->addChild(checker);

    for each (Player * player in _players) {
        this->addChild(player);
    }

    return true;
}

void GameScene::setupEventListeners()
{
    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    auto gameOver = cocos2d::EventListenerCustom::create("game_over", [&](cocos2d::EventCustom* e) {
        onVictory();
        });

    dispatcher->addEventListenerWithSceneGraphPriority(gameOver, this);

    auto restartGameListener = cocos2d::EventListenerCustom::create("restart_game", [&](cocos2d::EventCustom* e) {
        restartGame();
        });
    dispatcher->addEventListenerWithSceneGraphPriority(restartGameListener, this);
}

void GameScene::onVictory() {
    auto victory = VictoryScreen::create("VictoryScreen.png", "The Old One - World Destroyer");
    this->addChild(victory);
}

void GameScene::restartGame() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
}