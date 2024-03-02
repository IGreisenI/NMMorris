#include "StageController.h"
USING_NS_CC;

bool StageController::init() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_stageIndicator = Label::createWithTTF("Place", "fonts/arial.ttf", 20);    
	_stageIndicator->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(_stageIndicator);

	auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();

	auto playerNoMill = cocos2d::EventListenerCustom::create("player_no_mill", [&](cocos2d::EventCustom* event) {
		indicateStage("Place");
		});
	dispatcher->addEventListenerWithSceneGraphPriority(playerNoMill, this);

	auto playerMilling = cocos2d::EventListenerCustom::create("player_achieved_mill", [&](cocos2d::EventCustom* event) {
		indicateStage("Mill");
		}); 
	dispatcher->addEventListenerWithSceneGraphPriority(playerMilling, this);

	auto playerMilled = cocos2d::EventListenerCustom::create("player_played_mill", [&](cocos2d::EventCustom* event) {
		indicateStage("Place");
		});
	dispatcher->addEventListenerWithSceneGraphPriority(playerMilled, this);

	return true;
}

void StageController::indicateStage(std::string stageMessage) {
	_stageIndicator->setString(stageMessage);
}