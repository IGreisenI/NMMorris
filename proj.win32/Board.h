#pragma once
#include "cocos2d.h"
#include "Spot.h"

class Board : public cocos2d::Node
{
public:
	static Board* create(std::string boardSpriteName);
	virtual bool init(std::string boardSpriteName);

	virtual Spot* addSpot(float xPos, float yPos);

	virtual cocos2d::Rect getBoundingBoxOfSprite();
	
private:
	std::vector<Spot*> _boardSpots;
	cocos2d::Sprite* _boardSprite;
};