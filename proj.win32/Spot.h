#pragma once
#include "cocos2d.h"
#include "Piece.h"

class Spot : public cocos2d::Node
{
public:	
	static Spot* create(std::string spriteFileName); // Declare the static create method

	virtual bool init(std::string spriteFileName);
	virtual void placePiece(Piece* piece);
	virtual bool isOccupied();
	virtual Piece* getOccupyingPiece();
	virtual void removePiece();
	virtual void connectSpot(Spot* spot);
	virtual void connectSpots(std::vector<Spot*> spots);
private:
	Piece* _occupyingPiece;
	std::vector<Spot*> _connectingSpots;
};

