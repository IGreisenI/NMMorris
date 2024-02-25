#include "Board.h"
USING_NS_CC;

bool Board::init()
{
    auto windowSize = Director::getInstance()->getWinSizeInPixels();
    auto boardSprite = Sprite::create("board.png");
    this->addChild(boardSprite);
    this->setPosition(windowSize.width / 2, windowSize.height / 2);

    int distance = 64;
    addSpot(distance * -3, distance * 3);
    addSpot(distance * -2, distance * 2);
    addSpot(distance * -1, distance * 1);

    addSpot(distance * 0, distance * 3);
    addSpot(distance * 0, distance * 2);
    addSpot(distance * 0, distance * 1);

    addSpot(distance * 3, distance * 3);
    addSpot(distance * 2, distance * 2);
    addSpot(distance * 1, distance * 1);

    addSpot(distance * 3, distance * 0);
    addSpot(distance * 2, distance * 0);
    addSpot(distance * 1, distance * 0);

    addSpot(distance * 3, distance * -3);
    addSpot(distance * 2, distance * -2);
    addSpot(distance * 1, distance * -1);

    addSpot(distance * 0, distance * -3);
    addSpot(distance * 0, distance * -2);
    addSpot(distance * 0, distance * -1);

    addSpot(distance * -3, distance * -3);
    addSpot(distance * -2, distance * -2);
    addSpot(distance * -1, distance * -1);

    addSpot(distance * -3, distance * 0);
    addSpot(distance * -2, distance * 0);
    addSpot(distance * -1, distance * 0);

    return true;
}

void Board::addSpot(float xPos, float yPos) {
    Spot* spot = Spot::create("SpotTestSprite.png");
    spot->setPosition(xPos, yPos);
    this->addChild(spot);
}