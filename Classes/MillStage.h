#pragma once
#include "cocos2d.h"

#include "Spot.h"
#include "Player.h"
#include "Checker.h";

class MillStage
{
public:
	virtual void handleInput(cocos2d::Touch* touch, cocos2d::Event* event, Player* _opponentPlayer, Checker* _checker);
	void attemptMill(Piece* touchedPiece, Player* _opponentPlayer, Checker* _checker);
private:

};


