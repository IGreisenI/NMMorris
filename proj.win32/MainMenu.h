#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(MainMenu);
private:
    void createTitle();
    void createButtons();
    cocos2d::ui::Button* createButton(const std::string& text, float textSize);
    void startGame(cocos2d::Ref* sender);
    void quitGame(cocos2d::Ref* sender);
    void showSettings(cocos2d::Ref* sender);

};

