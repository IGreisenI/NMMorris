#pragma once
#include "cocos2d.h"
#include "PlayerInput.h"
#include "Player.h"

class TurnController : public cocos2d::Node
{
public:
    static TurnController* create(PlayerInput* playerInput, std::vector<Player*> players);
    virtual bool init(PlayerInput* playerInput, std::vector<Player*> players);

    // Method to switch to the next player's turn
    virtual void turn();
    virtual void nextTurn();

    CREATE_FUNC(PlayerInput);
private:
    std::vector<Player*> _players;
    PlayerInput* _playerInput;
    int _currentPlayerIndex;
};

