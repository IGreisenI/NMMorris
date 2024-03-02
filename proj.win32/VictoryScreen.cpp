#include "VictoryScreen.h"
USING_NS_CC;

VictoryScreen* VictoryScreen::create(std::string spriteName, std::string playerWonName) {
	VictoryScreen* victoryScreen = new (std::nothrow) VictoryScreen();
	if (victoryScreen && victoryScreen->init(spriteName, playerWonName)) {
		victoryScreen->autorelease();
		return victoryScreen;
	}
	CC_SAFE_DELETE(victoryScreen);
	return nullptr;
}

bool VictoryScreen::init(std::string spriteName, std::string playerWonName) {
    auto windowSize = Director::getInstance()->getWinSizeInPixels();
	_victorySprite = Sprite::create(spriteName);
    this->addChild(_victorySprite);
    this->setPosition(windowSize.width / 2, windowSize.height / 2);

	auto playerWonLabel = Label::createWithTTF("Winner: \n" + playerWonName, "fonts/arial.ttf", 20);
	playerWonLabel->setWidth(_victorySprite->getBoundingBox().getMaxX()*2 - 50);
	playerWonLabel->setTextColor(Color4B::BLACK);

	this->addChild(playerWonLabel);
	playerWonLabel->setPosition(0, _victorySprite->getBoundingBox().getMaxY() / 2);

	auto restartButton = ui::Button::create("Button.png", "ButtonSelected.png", "Button.png");
	auto restartButtonLabel = Label::createWithTTF("Restart", "fonts/arial.ttf", 20);
	restartButtonLabel->setTextColor(Color4B::BLACK);

	restartButton->addChild(restartButtonLabel);
	restartButtonLabel->setPosition(restartButton->getBoundingBox().getMaxX(), restartButton->getBoundingBox().getMaxY());
	restartButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("restart_game");
		});
	this->addChild(restartButton);

	return true;
}