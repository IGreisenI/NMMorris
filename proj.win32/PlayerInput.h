#pragma once
#include "cocos2d.h"
#include "Checker.h"
#include "Player.h"
#include "Spot.h"
#include "Piece.h"

class PlayerInput : public cocos2d::Node
{
public:
	static PlayerInput* create(std::vector<Player*> players, Checker* checker);
	virtual bool init(std::vector<Player*> players, Checker* checker);
	virtual void handleMillInput();
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	virtual void setActivePlayer(Player* player);
private:
	bool _isMilling;


	Checker* _checker;
	Piece* _selectedPiece;
	Player* _activePlayer;
	std::vector<Player*> _players;

	cocos2d::EventListenerTouchOneByOne* _touchListener;
	
	void setupEventListeners();

	virtual void attemptMill(Piece* touchedPiece);
	virtual void handlePieceTouch(Piece* touchedPiece);
	virtual void handleSpotTouch(Spot* touchedSpot);

	virtual bool checkPieceSelectionStage(Piece* piece);
	virtual bool checkSpotSelectionStage(Spot* touchedSpot);
}; 