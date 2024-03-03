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

    _players.push_back(Player::create("Blue Player", Color4B(75, 128, 194, 255)));
    _players.push_back(Player::create("Green Player", Color4B(98, 182, 70, 255)));

    Board* board = Board::create("board.png");

    _players.at(0)->setupPieces(9, 1, "Player1PieceV2.png", "Player1PieceV2Selected.png", board, board->getBoundingBoxOfSprite().getMinX(), board->getBoundingBoxOfSprite().getMinY());
    _players.at(0)->setupNameTextFields(Vec2(0,1), board, board->getBoundingBoxOfSprite().getMinX(), board->getBoundingBoxOfSprite().getMinY());

    _players.at(1)->setupPieces(9, -1, "Player2PieceV2.png", "Player2PieceV2Selected.png", board, board->getBoundingBoxOfSprite().getMaxX(), board->getBoundingBoxOfSprite().getMinY());
    _players.at(1)->setupNameTextFields(Vec2(1,1), board, board->getBoundingBoxOfSprite().getMaxX(), board->getBoundingBoxOfSprite().getMinY());

    Checker* checker = Checker::create(_players);
    StageController* stageController = StageController::create(checker);
    PlayerInput* playerInput = PlayerInput::create(_players, stageController);
    TurnController* turnController = TurnController::create(playerInput, _players, stageController);

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
        Player* winningPlayer = static_cast<Player*>(e->getUserData());
        onVictory(winningPlayer);
        });

    dispatcher->addEventListenerWithSceneGraphPriority(gameOver, this);

    auto restartGameListener = cocos2d::EventListenerCustom::create("restart_game", [&](cocos2d::EventCustom* e) {
        restartGame();
        });
    dispatcher->addEventListenerWithSceneGraphPriority(restartGameListener, this);
}

void GameScene::onVictory(Player* winningPlayer) {
    auto victory = VictoryScreen::create("VictoryScreen.png", winningPlayer);
    this->addChild(victory);
}

void GameScene::restartGame() {
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));

}