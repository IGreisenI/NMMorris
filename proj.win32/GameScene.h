#pragma once
#include "cocos2d.h";

#include "Board.h"
#include "Player.h"
#include "PlayerInput.h"
#include "TurnController.h"
#include "StageController.h"
#include "Checker.h";
#include "VictoryScreen.h";

class GameScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();

    virtual void onVictory();
    virtual void restartGame();

    CREATE_FUNC(GameScene);
private:
    std::vector<Player*> _players;
};

