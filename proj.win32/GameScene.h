#pragma once
#include "cocos2d.h";

class GameScene : public cocos2d::Layer
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();

    CREATE_FUNC(GameScene);
};

