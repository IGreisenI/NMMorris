#include "StageController.h"
USING_NS_CC;

StageController* StageController::create(Checker* checker) {
	StageController* stageController = new (std::nothrow) StageController();
	if (stageController && stageController->init(checker)) {
		stageController->autorelease();
		return stageController;
	}
	CC_SAFE_DELETE(stageController);
	return nullptr;
}

bool StageController::init(Checker* checker) {
	_checker = checker;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_stageIndicator = Label::createWithTTF("Place", "fonts/arial.ttf", 20);    
	_stageIndicator->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(_stageIndicator);

	setupEventListeners();

	_millStage = new MillStage();
	_placeStage = new PlaceStage();
	_moveStage = new MoveStage();
	_flyStage = new FlyStage();

	return true;
}

void StageController::setupEventListeners()
{
	auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();

	auto playerNoMill = cocos2d::EventListenerCustom::create("player_no_mill", [&](cocos2d::EventCustom* event) {
		indicateStage();
		});
	dispatcher->addEventListenerWithSceneGraphPriority(playerNoMill, this);

	auto playerMilling = cocos2d::EventListenerCustom::create("player_achieved_mill", [&](cocos2d::EventCustom* event) {
		_millAchieved = true;
		indicateStage();
		});
	dispatcher->addEventListenerWithSceneGraphPriority(playerMilling, this);

	auto playerMilled = cocos2d::EventListenerCustom::create("player_played_mill", [&](cocos2d::EventCustom* event) {
		_millAchieved = false;
		indicateStage();
		});
	dispatcher->addEventListenerWithSceneGraphPriority(playerMilled, this);
}

void StageController::indicateStage() {
	Color4B c = _activePlayer->getColor();
	_stageIndicator->setColor(Color3B(c.r, c.g, c.b));

	if(_millAchieved)
		_stageIndicator->setString("Mill");
	else if (!_activePlayer->isAllPiecesPlaced())
		_stageIndicator->setString("Place");
	else if (_activePlayer->isAllPiecesPlaced() && _activePlayer->getPieces().size() > 3)
		_stageIndicator->setString("Move");
	else if (_activePlayer->isAllPiecesPlaced() && _activePlayer->getPieces().size() <= 3)
		_stageIndicator->setString("Fly");
}

void StageController::handleInput(Touch* touch, Event* event, Player* _activePlayer, Player* _oppenentPlayer) {
	if (_millAchieved)
		_millStage->handleInput(touch, event, _oppenentPlayer, _checker);
	else if (!_activePlayer->isAllPiecesPlaced())
		_placeStage->handleInput(touch, event, _activePlayer);
	else if (_activePlayer->isAllPiecesPlaced() && _activePlayer->getPieces().size() > 3)
		_moveStage->handleInput(touch, event, _activePlayer);
	else if (_activePlayer->isAllPiecesPlaced() && _activePlayer->getPieces().size() <= 3)
		_flyStage->handleInput(touch, event, _activePlayer);
}

void StageController::setActivePlayer(Player* player) {
	_activePlayer = player;
	indicateStage();
}