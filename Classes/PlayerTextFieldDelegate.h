#pragma once
#include "cocos2d.h"
#include "Player.h"

class PlayerTextFieldDelegate : public cocos2d::TextFieldDelegate 
{
public:

    void setPlayer(Player* player);
    virtual bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF* sender);
private:
    Player* _player;
};

