#pragma once
#include "cocos2d.h"
#include "PlayerInput.h"
#include "StageController.h"
#include "Player.h"

class TurnController : public cocos2d::Node
{
public:
    static TurnController* create(PlayerInput* playerInput, std::vector<Player*> players, StageController* stageController);
    virtual bool init(PlayerInput* playerInput, std::vector<Player*> players, StageController* stageController);
    void setupEventListeners();
    virtual void createPlayerLabel();

    virtual void nextTurn();
private:
    int _currentPlayerIndex;
    std::vector<Player*> _players;
    PlayerInput* _playerInput;
    StageController* _stageController;
    cocos2d::Label* _playerTurnLabel;
};