#pragma once
#include "cocos2d.h"
#include "Spot.h"
#include "Player.h"

class Board : public cocos2d::Node
{
public:
	virtual bool init();
	void addSpot(float xPos, float yPos);

	//virtual bool tryFunction();
	//virtual bool placePiece(Spot* spot);
	//virtual bool movePiece(Spot* fromSpot, Spot* toSpot);
	//virtual bool removePiece(Spot* spot);
	//bool CheckForMill(Player player);
	//bool CheckForWin(Player player);

	CREATE_FUNC(Board);
private:
	Spot* _boardSpots[24];
};

