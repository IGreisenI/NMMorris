#include "Player.h"
USING_NS_CC;

bool Player::init() 
{

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);

    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}


bool Player::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    // Perform raycast
    PhysicsRayCastCallbackFunc callback = [&](PhysicsWorld& world, const PhysicsRayCastInfo& info, void* data) -> bool {
        auto node = info.shape->getBody()->getNode();

        if (node && dynamic_cast<Piece*>(node)) {
            _selectedPiece = dynamic_cast<Piece*>(node);
            
            return false;
        }

        if (node && dynamic_cast<Spot*>(node) && _selectedPiece) {
            Spot* spot = dynamic_cast<Spot*>(node);
            Spot* parentSpot= dynamic_cast<Spot*>(_selectedPiece->getParent());

            if (spot->isOccupied()) return false;

            if (parentSpot) {
                parentSpot->removePiece();
            }

            spot->placePiece(_selectedPiece);
            _selectedPiece = NULL;

            return false;
        }
        return true; // Continue raycast
    };

    auto physicsWorld = Director::getInstance()->getRunningScene()->getPhysicsWorld();
    physicsWorld->rayCast(callback, Vec2(location.x, location.y), Vec2(location.x, location.y), nullptr);

    return false; // Indicate that the touch was not handled

}
