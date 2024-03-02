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
    _spotSprite = Sprite::create(spriteFileName);
    this->addChild(_spotSprite);

    _spotAvaliableSprite = Sprite::create("SpotAvaliable.png");
    this->addChild(_spotAvaliableSprite);
    showAvaliable(false);

    auto physicsBody = PhysicsBody::createBox(_spotSprite->getContentSize());
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
    _occupyingPiece->moveToPosition(this->getPosition());
    _occupyingPiece->setPlaced(true);
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
    _connectingSpots.push_back(spot);
    spot->_connectingSpots.push_back(this);
}

void Spot::connectSpots(std::vector<Spot*> spots) {
    for each (Spot * spot in spots) {
        connectSpot(spot);
    }
}

std::vector<Spot*> Spot::getConnectingSpots() {
    return _connectingSpots;
}

void Spot::showAvaliable(bool avaliable) {
    _spotAvaliableSprite->setVisible(avaliable);
}

void Spot::showAvaliableConnectedSpots(bool showAvaliable) {
    for each (Spot* spot in _connectingSpots) {
        if(!spot->isOccupied()) spot->showAvaliable(showAvaliable);
    }
}
