#include "Player.h"
USING_NS_CC;

Player* Player::create(std::string name, cocos2d::Color4B playerColor) {
	Player* player = new (std::nothrow) Player();
	if (player && player->init(name, playerColor)) {
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player::init(std::string playerName, cocos2d::Color4B playerColor)
{
	_name = playerName;
	_playerColor = playerColor;
	return true;
}

void Player::setPlayerName(std::string playerName) {
	_name = playerName;
}

std::string Player::getName() {
	return _name;
}

void Player::setupNameTextFields(Vec2 anchorPoint, Node* board, int boardPositionX, int boardPositionY) {
	ui::TextField* player1Label = ui::TextField::create(_name, "fonts/arial.ttf", 20);
	player1Label->setPlaceHolderColor(_playerColor);
	player1Label->setTextColor(_playerColor);
	player1Label->addEventListener(CC_CALLBACK_2(Player::nameTextFieldEvent, this));

	board->addChild(player1Label);
	player1Label->setAnchorPoint(anchorPoint);
	player1Label->setPosition(Vec2(boardPositionX, boardPositionY));
}

void Player::nameTextFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type) {
	ui::TextField* textField = dynamic_cast<ui::TextField*>(sender);
	if (textField && type == ui::TextField::EventType::INSERT_TEXT) {
		setPlayerName(textField->getString());
	}
}

Color4B Player::getColor() {
	return _playerColor;
}

void Player::setupPieces(int amount, int minOrMaxMulti, std::string spriteFileName, std::string spriteSelectdFileName, Node* board, int boardPositionX, int boardPositionY) {
	for (int i = 0; i < 9; i++) {
		Piece* piece = Piece::create(spriteFileName, spriteSelectdFileName);
		board->addChild(piece);
		piece->setPosition(boardPositionX + piece->getPieceSprite()->getBoundingBox().getMinX() * minOrMaxMulti, boardPositionY + piece->getChildren().at(0)->getBoundingBox().getMaxY() + piece->getChildren().at(0)->getBoundingBox().getMaxY() * 2 * i);
		addPieceToPlayer(piece);
	}
}

void Player::addPieceToPlayer(Piece* piece) {
	_pieces.push_back(piece);
}

void Player::removePieceToPlayer(Piece* piece) {
	_pieces.erase(std::remove(_pieces.begin(), _pieces.end(), piece), _pieces.end());
}

bool Player::isPlayerPiece(Piece* piece) {
	for each (Piece * p in _pieces) {
		if (p == piece) return true;
	}
	return false;
}

std::vector<Piece*> Player::getPieces() {
	return _pieces;
}

bool Player::isAllPiecesPlaced() {
	for each (Piece * piece in _pieces) {
		if (!piece->isPlaced()) return false;
	}
	return true;
}