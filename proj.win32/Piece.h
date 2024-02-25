#pragma once
#include "cocos2d.h"

class Piece : public cocos2d::Node
{
public:
	static Piece* create(std::string spriteFileName); // Declare the static create method

	virtual bool init(std::string spriteFileName);
	//virtual bool isPlaced();
	//virtual void move();

};

