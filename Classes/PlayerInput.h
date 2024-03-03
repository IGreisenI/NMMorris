#pragma once
#include "cocos2d.h"

#include "Checker.h"
#include "Player.h"
#include "Spot.h"
#include "Piece.h"
#include "StageController.h"

class PlayerInput : public cocos2d::Node
{
public:
	static PlayerInput* create(std::vector<Player*> players, Checker* checker, StageController* stageController);
	virtual bool init(std::vector<Player*> players, Checker* checker, StageController* stageController);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	virtual void setActivePlayer(Player* player);
private:
	bool _isMilling;

	StageController* _stageController;
	Checker* _checker;
	Player* _activePlayer;
	std::vector<Player*> _players;

	cocos2d::EventListenerTouchOneByOne* _touchListener;
	
	void setupEventListeners();

}; 