#pragma once
#include "cocos2d.h"

class Piece : public cocos2d::Node
{
public:
	static Piece* create(std::string spriteFileName, std::string spriteSelectdFileName); // Declare the static create method

	virtual bool init(std::string spriteFileName, std::string spriteSelectdFileName);
	virtual bool isPlaced();
	virtual void setPlaced(bool isPlaced);
	virtual void moveToPosition(cocos2d::Vec2 position);

	virtual void select(bool isSelected);

	virtual cocos2d::Sprite* getPieceSprite();

	virtual void destroy();


	//virtual void move();
private:
	bool _isPlaced;
	cocos2d::Sprite* _pieceSprite;
	cocos2d::Sprite* _pieceSelectedSprite;
};

