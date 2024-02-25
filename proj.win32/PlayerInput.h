#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Spot.h"
#include "Piece.h"

class PlayerInput : public cocos2d::Node
{
public:
	virtual bool init();
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	virtual void setActivePlayer(Player* player);
	CREATE_FUNC(PlayerInput);
private:
	Player* _activePlayer;
	Piece* _selectedPiece;

	virtual void handlePieceTouch(Piece* touchedPiece);
	virtual void handleSpotTouch(Spot* touchedSpot);
};