#include "Piece.h"
USING_NS_CC;

Piece* Piece::create(std::string spriteFileName, std::string spriteSelectdFileName) {
    Piece* piece = new (std::nothrow) Piece();
    if (piece && piece->init(spriteFileName, spriteSelectdFileName)) {
        piece->autorelease();
        return piece;
    }
    CC_SAFE_DELETE(piece);
    return nullptr;
}

bool Piece::init(std::string spriteFileName, std::string spriteSelectdFileName) {
    _pieceSprite = Sprite::create(spriteFileName);
    this->addChild(_pieceSprite);

    _pieceSelectedSprite = Sprite::create(spriteSelectdFileName);
    this->addChild(_pieceSelectedSprite);
    _pieceSelectedSprite->setVisible(false);
    
    auto physicsBody = PhysicsBody::createBox(_pieceSprite->getContentSize());
    physicsBody->setDynamic(false);
    physicsBody->setCollisionBitmask(0x02);
    this->addComponent(physicsBody);

    this->setName("Piece");

    return true;
}

void Piece::setPlaced(bool isPlaced) {
    _isPlaced = isPlaced;
}

bool Piece::isPlaced() {
    return _isPlaced;
}

void Piece::moveToPosition(Vec2 position) {
    auto moveTo = MoveTo::create(0.5f, position);   

    this->runAction(moveTo);
}

void Piece::select(bool isSelected) {
    _pieceSprite->setVisible(!isSelected);
    _pieceSelectedSprite->setVisible(isSelected);
}

Sprite* Piece::getPieceSprite() {
    return _pieceSprite;
}

void Piece::destroy() {
    removeAllChildrenWithCleanup(true);
    removeFromParentAndCleanup(true);
    setPosition(-10000, -10000);
}