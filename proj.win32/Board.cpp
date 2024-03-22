#include "Board.h"
USING_NS_CC;

Board* Board::create(std::string boardSpriteName) {
    Board* board = new (std::nothrow) Board();
    if (board && board->init(boardSpriteName)) {
        board->autorelease();
        return board;
    }
    CC_SAFE_DELETE(board);
    return nullptr;
}

bool Board::init(std::string boardSpriteName)
{
    auto windowSize = Director::getInstance()->getWinSizeInPixels();
    _boardSprite = Sprite::create(boardSpriteName);
    this->addChild(_boardSprite);
    this->setPosition(windowSize.width / 2, windowSize.height / 2);

    int distance = 64;
    
    /* 
    Create 24 spots and position them
    This is following the pattern:
        x   .   .
         x  .  .
          x . .
        ...   ...
          . . .
         .  .  .
        .   .   .

    Objects marked with x are first.
    Going from top left clock wise.
    */

    Spot* thirdLeftTop = addSpot(distance * -3, distance * 3);
    Spot* secondLeftTop = addSpot(distance * -2, distance * 2);
    Spot* firstLeftTop = addSpot(distance * -1, distance * 1);

    Spot* thirdMiddleTop = addSpot(distance * 0, distance * 3);
    Spot* secondMiddleTop = addSpot(distance * 0, distance * 2);
    Spot* firstMiddleTop = addSpot(distance * 0, distance * 1);

    Spot* thirdRightTop = addSpot(distance * 3, distance * 3);
    Spot* secondRightTop = addSpot(distance * 2, distance * 2);
    Spot* firstRightTop = addSpot(distance * 1, distance * 1);

    Spot* thirdRightMiddle = addSpot(distance * 3, distance * 0);
    Spot* secondRightMiddle = addSpot(distance * 2, distance * 0);
    Spot* firstRightMiddle = addSpot(distance * 1, distance * 0);

    Spot* thirdRightDown = addSpot(distance * 3, distance * -3);
    Spot* secondRightDown = addSpot(distance * 2, distance * -2);
    Spot* firstRightDown = addSpot(distance * 1, distance * -1);

    Spot* thirdMiddleDown = addSpot(distance * 0, distance * -3);
    Spot* secondMiddleDown = addSpot(distance * 0, distance * -2);
    Spot* firstMiddleDown = addSpot(distance * 0, distance * -1);

    Spot* thirdLeftDown = addSpot(distance * -3, distance * -3);
    Spot* secondLeftDown = addSpot(distance * -2, distance * -2);
    Spot* firstLeftDown = addSpot(distance * -1, distance * -1);

    Spot* thirdLeftMiddle = addSpot(distance * -3, distance * 0);
    Spot* secondLeftMiddle = addSpot(distance * -2, distance * 0);
    Spot* firstLeftMiddle = addSpot(distance * -1, distance * 0);

    _boardSpots = std::vector<Spot*>
    { 
        thirdLeftTop, secondLeftTop, secondLeftTop,
        thirdMiddleTop, secondMiddleTop, firstLeftTop,
        thirdRightTop, secondRightTop, firstRightTop,
        thirdRightMiddle, secondRightMiddle, firstRightMiddle,
        thirdRightDown, secondRightDown, firstRightDown,
        thirdMiddleDown, secondMiddleDown, firstMiddleDown,
        thirdLeftDown, secondLeftDown, firstLeftDown,
        thirdLeftMiddle, secondLeftMiddle, firstLeftMiddle
    };

    // Connect spots in a nine mans morris way!
    thirdLeftTop->connectSpots({ thirdLeftMiddle, thirdMiddleTop });
    secondLeftTop->connectSpots({ secondLeftMiddle, secondMiddleTop });
    firstLeftTop->connectSpots({ firstLeftMiddle, firstMiddleTop });

    thirdRightTop->connectSpots({ thirdRightMiddle, thirdMiddleTop });
    secondRightTop->connectSpots({ secondRightMiddle, secondMiddleTop });
    firstRightTop->connectSpots({ firstRightMiddle, firstMiddleTop });

    thirdRightDown->connectSpots({ thirdRightMiddle, thirdMiddleDown });
    secondRightDown->connectSpots({ secondRightMiddle, secondMiddleDown });
    firstRightDown->connectSpots({ firstRightMiddle, firstMiddleDown });

    thirdLeftDown->connectSpots({ thirdLeftMiddle, thirdMiddleDown });
    secondLeftDown->connectSpots({ secondLeftMiddle, secondMiddleDown });
    firstLeftDown->connectSpots({ firstLeftMiddle, firstMiddleDown });

    secondMiddleTop->connectSpots({ thirdMiddleTop, firstMiddleTop });
    secondRightMiddle->connectSpots({ thirdRightMiddle, firstRightMiddle });
    secondMiddleDown->connectSpots({ thirdMiddleDown, firstMiddleDown });
    secondLeftMiddle->connectSpots({ thirdLeftMiddle, firstLeftMiddle });

    return true;
}

Spot* Board::addSpot(float xPos, float yPos) {
    Spot* spot = Spot::create("SpotSprite.png");
    spot->setPosition(xPos, yPos);
    this->addChild(spot);
    return spot;
}

Rect Board::getBoundingBoxOfSprite() {
    return _boardSprite->getBoundingBox();
}