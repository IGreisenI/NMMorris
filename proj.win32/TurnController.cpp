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

    auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
    auto playerInputFinishedListener = cocos2d::EventListenerCustom::create("player_placed_piece", [&](cocos2d::EventCustom* event) {
        turn();
        });
    dispatcher->addEventListenerWithSceneGraphPriority(playerInputFinishedListener, this);


	return true;
}

void TurnController::turn() {

    //if (player managed to succeed) {
        nextTurn();
    //}
}

void TurnController::nextTurn() {
	_currentPlayerIndex = (_currentPlayerIndex + 1) % (int)_players.size();
	_playerInput->setActivePlayer(_players.at(_currentPlayerIndex));
}