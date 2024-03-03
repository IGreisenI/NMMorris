#pragma once
#include "cocos2d.h"

#include "Player.h"
#include "StageController.h"

class PlayerInput : public cocos2d::Node
{
public:
	static PlayerInput* create(std::vector<Player*> players, StageController* stageController);
	virtual bool init(std::vector<Player*> players, StageController* stageController);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	virtual void setActivePlayer(Player* player);
private:
	StageController* _stageController;
	Player* _activePlayer;
	std::vector<Player*> _players;

	cocos2d::EventListenerTouchOneByOne* _touchListener;
	
	void setupEventListeners();

}; 