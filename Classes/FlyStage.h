#pragma once
#include "cocos2d.h"

#include "Spot.h"
#include "Player.h"

class FlyStage
{
public:
	virtual void handleInput(cocos2d::Touch* touch, cocos2d::Event* event, Player* _activePlayer);
	void handlePieceTouch(Piece* touchedPiece, Player* _activePlayer);
	void handleSpotTouch(Spot* touchedSpot);

private:
	Piece* _selectedPiece;
};

