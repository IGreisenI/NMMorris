#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Player.h"

class VictoryScreen : public cocos2d::Node
{
public:
    static VictoryScreen* create(std::string spriteName, Player* winningPlayer);
    virtual bool init(std::string spriteName, Player* winningPlayer);
private:
    cocos2d::Sprite* _victorySprite;
};

