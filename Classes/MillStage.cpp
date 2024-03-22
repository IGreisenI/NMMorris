#include "MillStage.h"
USING_NS_CC;

void MillStage::handleInput(cocos2d::Touch* touch, cocos2d::Event* event, Player* _opponentPlayer, Checker* _checker) {
    auto location = touch->getLocation();

    // Perform raycast
    PhysicsRayCastCallbackFunc callback = [&](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data) -> bool {
        auto node = info.shape->getBody()->getNode();

        if (node && dynamic_cast<Piece*>(node) && _opponentPlayer->isPlayerPiece(dynamic_cast<Piece*>(node))) {
            attemptMill(dynamic_cast<Piece*>(node), _opponentPlayer, _checker);
            return false;
        }

        return true; // Continue raycast
    };

    auto physicsWorld = Director::getInstance()->getRunningScene()->getPhysicsWorld();
    physicsWorld->rayCast(callback, Vec2(location.x, location.y), Vec2(location.x, location.y), nullptr);

}

void MillStage::attemptMill(Piece* touchedPiece, Player* _opponentPlayer, Checker* _checker)
{
    if (!touchedPiece->isPlaced()) return;
    if (_checker->checkForMill(dynamic_cast<Spot*>(touchedPiece->getParent()), _opponentPlayer)) {
        for each (Piece * piece in _opponentPlayer->getPieces()) {
            if (dynamic_cast<Spot*>(piece->getParent()) && !_checker->checkForMill(dynamic_cast<Spot*>(piece->getParent()), _opponentPlayer)) return;
        }
    }

    if (dynamic_cast<Spot*>(touchedPiece->getParent())) {
        dynamic_cast<Spot*>(touchedPiece->getParent())->removePiece();
    }

    _opponentPlayer->removePieceToPlayer(touchedPiece);

    touchedPiece->destroy();

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent("player_played_mill");
}