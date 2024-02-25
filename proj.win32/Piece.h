#pragma once
#include "cocos2d.h"
#include "Player.h"

class Piece : public cocos2d::Node
{
public:
	static Piece* create(std::string spriteFileName); // Declare the static create method

	virtual bool init(std::string spriteFileName);
	virtual void setOwner(Player* owner);
	virtual Player* getOwner();

	//virtual bool isPlaced();
	//virtual void move();
private:
	Player* _owner;
};

