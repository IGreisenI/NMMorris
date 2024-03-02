#pragma once
#include "cocos2d.h"
#include "PlayerInput.h"
#include "Player.h"

class TurnController : public cocos2d::Node
{
public:
    static TurnController* create(PlayerInput* playerInput, std::vector<Player*> players);
    virtual bool init(PlayerInput* playerInput, std::vector<Player*> players);
    virtual void createPlayerLabel();

    virtual void nextTurn();
private:
    int _currentPlayerIndex;
    std::vector<Player*> _players;
    PlayerInput* _playerInput;
    cocos2d::Label* _playerTurnLabel;
};