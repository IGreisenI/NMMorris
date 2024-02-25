#pragma once
#include "cocos2d.h"
#include "Piece.h"
#include "Spot.h"

class Player : public cocos2d::Node
{
public:
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	//virtual void setTurn();

	CREATE_FUNC(Player);
private:
	std::string _name;
	Piece* _selectedPiece;
	int _piecesLeft;
	bool _isTurn;
};