#include "PlayerInput.h"
USING_NS_CC;

PlayerInput* PlayerInput::create(std::vector<Player*> players) {
    PlayerInput* playerInput = new (std::nothrow) PlayerInput();
    if (playerInput && playerInput->init(players)) {
        playerInput->autorelease();
        return playerInput;
    }
    CC_SAFE_DELETE(playerInput);
    return nullptr;
}

bool PlayerInput::init(std::vector<Player*> players)
{
    _players = players;
    auto dispatcher = Director::getInstance()->getEventDispatcher();

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(PlayerInput::onTouchBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    auto keyEventListener = EventListenerKeyboard::create();
    keyEventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_R)
            dispatcher->dispatchCustomEvent("restart_game");
    };
    dispatcher->addEventListenerWithSceneGraphPriority(keyEventListener, this);
    
    auto playerInputFinishedListener = cocos2d::EventListenerCustom::create("player_achieved_mill", [&](cocos2d::EventCustom* event) {
        handleMillInput();
        });

    dispatcher->addEventListenerWithSceneGraphPriority(playerInputFinishedListener, this);
    return true;
}

bool PlayerInput::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    // Perform raycast
    PhysicsRayCastCallbackFunc callback = [&](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data) -> bool {
        auto node = info.shape->getBody()->getNode();

        if (_isMilling && node && dynamic_cast<Piece*>(node) && !_activePlayer->isPlayerPiece(dynamic_cast<Piece*>(node))) {
            attemptMill(dynamic_cast<Piece*>(node));
            return false;
        }

        if (node && dynamic_cast<Piece*>(node) && _activePlayer->isPlayerPiece(dynamic_cast<Piece*>(node)) && checkPieceSelectionStage(dynamic_cast<Piece*>(node))) {
            handlePieceTouch(dynamic_cast<Piece*>(node));
            return false;
        }

        if (node && dynamic_cast<Spot*>(node) && _selectedPiece && checkSpotSelectionStage(dynamic_cast<Spot*>(node))) {
            handleSpotTouch(dynamic_cast<Spot*>(node));
            return false;
        }

        return true; // Continue raycast
    };

    auto physicsWorld = Director::getInstance()->getRunningScene()->getPhysicsWorld();
    physicsWorld->rayCast(callback, Vec2(location.x, location.y), Vec2(location.x, location.y), nullptr);

    return false; // Indicate that the touch was not handled
}

bool PlayerInput::checkPieceSelectionStage(Piece* piece) {
    auto playerPieces = _activePlayer->getPieces();
    for each (Piece * p in playerPieces) {
        if (!p->isPlaced() && piece->isPlaced()) return false;
    }
    return true;
}

bool PlayerInput::checkSpotSelectionStage(Spot* touchedSpot) {
    if (touchedSpot->isOccupied()) return false;

    if (_activePlayer->getPieces().size() <= 3 || !_activePlayer->isAllPiecesPlaced()) return true;
    
    Spot* connectedSpots = dynamic_cast<Spot*>(_selectedPiece->getParent());
    for each (Spot* spot in connectedSpots->getConnectingSpots()) {
        if (spot == touchedSpot) return true;
    }

    return false;
}

void PlayerInput::handleMillInput() {

    _isMilling = true;
}

void PlayerInput::attemptMill(Piece* touchedPiece)
{
    if (!touchedPiece->isPlaced()) return;

    if (dynamic_cast<Spot*>(touchedPiece->getParent())) {
        dynamic_cast<Spot*>(touchedPiece->getParent())->removePiece();
    }


    for each (Player * player in _players) {
        if (player->isPlayerPiece(touchedPiece)) player->removePieceToPlayer(touchedPiece);
    }

    // Yeah idk how to properly delete it, we doing this skyrim style, purgatory
    touchedPiece->destroy();


    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent("player_played_mill");

    _isMilling = false;
}

void PlayerInput::handlePieceTouch(Piece* touchedPiece)
{
    if(_selectedPiece){
        _selectedPiece->select(false);
        Spot* parentSpot = dynamic_cast<Spot*>(_selectedPiece->getParent());
        if (parentSpot) parentSpot->showAvaliableConnectedSpots(false);
    }

    Spot* parentSpot = dynamic_cast<Spot*>(touchedPiece->getParent());
    if (parentSpot) parentSpot->showAvaliableConnectedSpots(true);

    _selectedPiece = touchedPiece;
    _selectedPiece->select(true);
}

void PlayerInput::handleSpotTouch(Spot* touchedSpot)
{

    Spot* parentSpot = dynamic_cast<Spot*>(_selectedPiece->getParent());
    if (parentSpot) {
        parentSpot->removePiece();
        parentSpot->showAvaliableConnectedSpots(false);
    }

    touchedSpot->placePiece(_selectedPiece);
    _selectedPiece->select(false);

    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("player_placed_piece", _selectedPiece);
    _selectedPiece = nullptr;
}

void PlayerInput::setActivePlayer(Player* player) {
    _activePlayer = player;
}