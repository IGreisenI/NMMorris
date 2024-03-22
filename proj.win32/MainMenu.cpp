#include "MainMenu.h"
#include "GameScene.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();

    auto layer = MainMenu::create();
    scene->addChild(layer);

    return scene;
}

bool MainMenu::init()
{
    // Create UI elements
    createTitle();
    createButtons();

    return true;

}

void MainMenu::createTitle()
{
    // Get the visible size of the screen
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Create and position the title label
    auto titleLabel = Label::createWithTTF("Nine Men's Morris", "fonts/arial.ttf", 36);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 50));
    this->addChild(titleLabel);
}

void MainMenu::createButtons()
{
    // Get the visible size of the screen
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Create a start button
    auto startButton = MenuItemLabel::create(Label::createWithTTF("Start", "fonts/arial.ttf", 24), CC_CALLBACK_1(MainMenu::startGame, this));
    startButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    // Create a quit button
    auto quitButton = MenuItemLabel::create(Label::createWithTTF("Quit", "fonts/arial.ttf", 24), CC_CALLBACK_1(MainMenu::quitGame, this));
    quitButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 100));

    // Create a menu with the buttons
    auto menu = Menu::create(startButton, quitButton, nullptr);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);
}

ui::Button* MainMenu::createButton(const std::string& text, float textSize)
{
    // Create button
    auto button = ui::Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
    button->setTitleText(text);
    button->setTitleFontSize(textSize);
    return button;
}

void MainMenu::startGame(Ref* sender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
}

void MainMenu::quitGame(Ref* sender)
{
    Director::getInstance()->end();
}
