#pragma once
#include "cocos2d.h"
#include "Piece.h"

class Player : public cocos2d::Node
{
public:
	static Player* create(std::string playerName);
	virtual bool init(std::string playerName);

	virtual std::string getName();

	virtual void addPieceToPlayer(Piece* piece);
	virtual void removePieceToPlayer(Piece* piece);
	virtual bool isPlayerPiece(Piece* piece);
	virtual bool isAllPiecesPlaced();
	virtual std::vector<Piece*> getPieces();
private:
	std::string _name;
	std::vector<Piece*> _pieces;
	bool _isTurn;
};