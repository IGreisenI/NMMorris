#include "TurnController.h"
USING_NS_CC;

TurnController* TurnController::create(PlayerInput* playerInput, std::vector<Player*> players) {
    TurnController* turnController = new (std::nothrow) TurnController();
    if (turnController && turnController->init(playerInput, players)) {
        turnController->autorelease();
        return turnController;
    }
    CC_SAFE_DELETE(turnController);
    return nullptr;
}

bool TurnController::init(PlayerInput* playerInput, std::vector<Player*> players) {

    _players = players;
    _playerInput = playerInput;
	_currentPlayerIndex = random(0, (int)_players.size() - 1);
	_playerInput->setActivePlayer(_players.at(_currentPlayerIndex));

    createPlayerLabel();

    setupEventListeners();

	return true;
}

void TurnController::setupEventListeners()
{
    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    auto playerNoMill = cocos2d::EventListenerCustom::create("player_no_mill", [&](cocos2d::EventCustom* event) {
        nextTurn();
        });
    dispatcher->addEventListenerWithSceneGraphPriority(playerNoMill, this);
    auto playerPlayedMill = cocos2d::EventListenerCustom::create("player_played_mill", [&](cocos2d::EventCustom* event) {
        nextTurn();
        });
    dispatcher->addEventListenerWithSceneGraphPriority(playerPlayedMill, this);
}

void TurnController::nextTurn() {
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("end_turn", _players.at(_currentPlayerIndex));

	_currentPlayerIndex = (_currentPlayerIndex + 1) % (int)_players.size();
	_playerInput->setActivePlayer(_players.at(_currentPlayerIndex));

    _playerTurnLabel->setString("Active turn: " + _players.at(_currentPlayerIndex)->getName());
}

void TurnController::createPlayerLabel() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto turnLabel = Label::createWithTTF("Active turn: " + _players.at(_currentPlayerIndex)->getName(), "fonts/arial.ttf", 20);
    turnLabel->setAnchorPoint(Vec2(0,0));
    turnLabel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 256, origin.y + visibleSize.height - 130));
    this->addChild(turnLabel);
    _playerTurnLabel = turnLabel;
}