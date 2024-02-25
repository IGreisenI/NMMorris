#include "Piece.h"
USING_NS_CC;

Piece* Piece::create(std::string spriteFileName) {
    Piece* piece = new (std::nothrow) Piece();
    if (piece && piece->init(spriteFileName)) {
        piece->autorelease();
        return piece;
    }
    CC_SAFE_DELETE(piece);
    return nullptr;
}

bool Piece::init(std::string spriteFileName) {
    auto pieceSprite = Sprite::create(spriteFileName);
    this->addChild(pieceSprite);
    
    auto physicsBody = PhysicsBody::createBox(pieceSprite->getContentSize());
    physicsBody->setDynamic(false);
    physicsBody->setCollisionBitmask(0x02);
    this->addComponent(physicsBody);

    this->setName("Piece");

    return true;
}

void Piece::setOwner(Player* owner) {
    _owner = owner;
}

Player* Piece::getOwner() {
    return _owner;
}