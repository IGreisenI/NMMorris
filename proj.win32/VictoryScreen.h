#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class VictoryScreen : public cocos2d::Node
{
public:
    static VictoryScreen* create(std::string spriteName, std::string playerWonName);
    virtual bool init(std::string spriteName, std::string playerWonName);
private:
    cocos2d::Sprite* _victorySprite;
};

