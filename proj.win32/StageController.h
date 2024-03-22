#pragma once
#include "cocos2d.h"

#include "PlaceStage.h"
#include "MoveStage.h"
#include "MillStage.h"
#include "FlyStage.h"

class StageController : public cocos2d::Node
{
public:
	static StageController* create(Checker* checker);
	virtual bool init(Checker* checker);
	void setupEventListeners();
	virtual void indicateStage();
	void handleInput(cocos2d::Touch* touch, cocos2d::Event* event, Player* _activePlayer, Player* _oppenentPlayer);
	void setActivePlayer(Player* player);
private:
	bool _millAchieved;

	PlaceStage* _placeStage;
	MoveStage* _moveStage;
	MillStage* _millStage;
	FlyStage* _flyStage;

	Player* _activePlayer;
	Checker* _checker;
	cocos2d::Label* _stageIndicator;
};

