#pragma once
#include "cocos2d.h";
#include "ui/CocosGUI.h"

#include "Board.h"
#include "Player.h"
#include "PlayerInput.h"
#include "PlayerTextFieldDelegate.h"

#include "TurnController.h"
#include "StageController.h"
#include "Checker.h";
#include "VictoryScreen.h";

class GameScene : public cocos2d::Layer
{
public:
    virtual bool init();
    void setupEventListeners();
    static cocos2d::Scene* createScene();

    virtual void onVictory(Player* winningPlayer);
    virtual void restartGame();

    CREATE_FUNC(GameScene);

private:
    std::vector<Player*> _players;
};

