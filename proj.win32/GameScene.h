#pragma once
#include "cocos2d.h";

#include "Board.h"
#include "Player.h"
#include "PlayerInput.h"
#include "TurnController.h"

class GameScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();

    CREATE_FUNC(GameScene);
private:
    std::vector<Player*> _players;
};

