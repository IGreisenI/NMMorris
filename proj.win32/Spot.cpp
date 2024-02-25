#include "Spot.h"
USING_NS_CC;

Spot* Spot::create(std::string spriteFileName) {
    Spot* spot = new (std::nothrow) Spot();
    if (spot && spot->init(spriteFileName)) {
        spot->autorelease();
        return spot;
    }
    CC_SAFE_DELETE(spot);
    return nullptr;
}

bool Spot::init(std::string spriteFileName) {
    auto spotSprite = Sprite::create(spriteFileName);
    this->addChild(spotSprite);


    auto physicsBody = PhysicsBody::createBox(spotSprite->getContentSize());
    physicsBody->setDynamic(false);
    physicsBody->setCollisionBitmask(0x01);
    physicsBody->setContactTestBitmask(0x01);
    this->addComponent(physicsBody);

    this->setName("Spot");
    return true;
}

void Spot::placePiece(Piece* piece) {
    _occupyingPiece = piece;
    _occupyingPiece->setParent(this);
    _occupyingPiece->setPosition(this->getPosition());
}

bool Spot::isOccupied() {
    return _occupyingPiece != nullptr;
}

Piece* Spot::getOccupyingPiece() {
    return _occupyingPiece;
}

void Spot::removePiece() {
    _occupyingPiece = NULL;
}

void Spot::connectSpot(Spot* spot) {
    _connectingSpots.push_back(spot);;
}