#include "PlayerInput.h"
USING_NS_CC;

PlayerInput* PlayerInput::create(std::vector<Player*> players, StageController* stageController) {
    PlayerInput* playerInput = new (std::nothrow) PlayerInput();
    if (playerInput && playerInput->init(players, stageController)) {
        playerInput->autorelease();
        return playerInput;
    }
    CC_SAFE_DELETE(playerInput);
    return nullptr;
}

bool PlayerInput::init(std::vector<Player*> players, StageController* stageController)
{
    _players = players;
    _stageController = stageController;
    setupEventListeners();
    return true;
}

void PlayerInput::setupEventListeners()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(PlayerInput::onTouchBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    auto restartKeyEventListener = EventListenerKeyboard::create();
    restartKeyEventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_TAB)
            dispatcher->dispatchCustomEvent("restart_game");
    };
    dispatcher->addEventListenerWithSceneGraphPriority(restartKeyEventListener, this);
}

bool PlayerInput::onTouchBegan(Touch* touch, Event* event)
{
    Player* opponentPlayer;
    for each (Player * player in _players) {
        if (player != _activePlayer) opponentPlayer = player;
    }

    _stageController->handleInput(touch, event, _activePlayer, opponentPlayer);
    return true;
}

void PlayerInput::setActivePlayer(Player* player) {
    _activePlayer = player;
}