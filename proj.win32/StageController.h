#pragma once
#include "cocos2d.h"

class StageController : public cocos2d::Node
{
public:
	virtual bool init();
	void setupEventListeners();
	virtual void indicateStage(std::string stageMessage);

	CREATE_FUNC(StageController);
private:
	cocos2d::Label* _stageIndicator;
};

