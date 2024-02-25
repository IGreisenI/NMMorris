#pragma once
#include "cocos2d.h"

class Player : public cocos2d::Node
{
public:
	virtual bool init();
	//virtual void setTurn();

	CREATE_FUNC(Player);
private:
	std::string _name;
	int _piecesLeft;
	bool _isTurn;
};