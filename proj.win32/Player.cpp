#include "Player.h"
USING_NS_CC;

Player* Player::create(std::string name, cocos2d::Color3B playerColor) {
	Player* player = new (std::nothrow) Player();
	if (player && player->init(name, playerColor)) {
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player::init(std::string playerName, cocos2d::Color3B playerColor)
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

Color3B Player::getColor() {
	return _playerColor;
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