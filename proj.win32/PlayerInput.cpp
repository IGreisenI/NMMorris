#include "PlayerInput.h"
USING_NS_CC;

bool PlayerInput::init()
{

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayerInput::onTouchBegan, this);

    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}


bool PlayerInput::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    // Perform raycast
    PhysicsRayCastCallbackFunc callback = [&](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data) -> bool {
        auto node = info.shape->getBody()->getNode();

        if (node && dynamic_cast<Piece*>(node) && dynamic_cast<Piece*>(node)->getOwner() == _activePlayer) {
            handlePieceTouch(dynamic_cast<Piece*>(node));
            return false;
        }

        if (node && dynamic_cast<Spot*>(node) && _selectedPiece) {
            handleSpotTouch(dynamic_cast<Spot*>(node));
            return false;
        }
        return true; // Continue raycast
    };

    auto physicsWorld = Director::getInstance()->getRunningScene()->getPhysicsWorld();
    physicsWorld->rayCast(callback, Vec2(location.x, location.y), Vec2(location.x, location.y), nullptr);

    return false; // Indicate that the touch was not handled

}

void PlayerInput::handlePieceTouch(Piece* touchedPiece)
{
    _selectedPiece = touchedPiece;
}

void PlayerInput::handleSpotTouch(Spot* touchedSpot)
{
    if (touchedSpot->isOccupied()) return;

    Spot* parentSpot = dynamic_cast<Spot*>(_selectedPiece->getParent());
    if (parentSpot) {
        parentSpot->removePiece();
    }

    touchedSpot->placePiece(_selectedPiece);

    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("player_placed_piece");
    _selectedPiece = nullptr;
}

void PlayerInput::setActivePlayer(Player* player) {
    _activePlayer = player;
}