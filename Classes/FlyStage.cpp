#include "FlyStage.h"
USING_NS_CC;

void FlyStage::handleInput(cocos2d::Touch* touch, cocos2d::Event* event, Player* _activePlayer) {
    auto location = touch->getLocation();

    // Perform raycast
    PhysicsRayCastCallbackFunc callback = [&](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data) -> bool {
        auto node = info.shape->getBody()->getNode();


        if (node && dynamic_cast<Piece*>(node) && _activePlayer->isPlayerPiece(dynamic_cast<Piece*>(node))) {
            handlePieceTouch(dynamic_cast<Piece*>(node), _activePlayer);
            return false;
        }

        if (node && dynamic_cast<Spot*>(node) && _selectedPiece && !dynamic_cast<Spot*>(node)->isOccupied()) {
            handleSpotTouch(dynamic_cast<Spot*>(node));
            return false;
        }

        return true; // Continue raycast
    };

    auto physicsWorld = Director::getInstance()->getRunningScene()->getPhysicsWorld();
    physicsWorld->rayCast(callback, Vec2(location.x, location.y), Vec2(location.x, location.y), nullptr);

}

void FlyStage::handlePieceTouch(Piece* touchedPiece, Player* _activePlayer)
{
    if (_selectedPiece) {
        Spot* parentSpot = dynamic_cast<Spot*>(_selectedPiece->getParent());
        if (parentSpot) parentSpot->showAvaliableConnectedSpots(false);

        _selectedPiece->select(false);
    }

    Spot* parentSpot = dynamic_cast<Spot*>(touchedPiece->getParent());
    if (parentSpot && !_activePlayer->isAllPiecesPlaced() && _activePlayer->getPieces().size() > 3)
        parentSpot->showAvaliableConnectedSpots(true);

    _selectedPiece = touchedPiece;
    _selectedPiece->select(true);
}

void FlyStage::handleSpotTouch(Spot* touchedSpot)
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