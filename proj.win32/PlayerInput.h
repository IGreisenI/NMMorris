#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Spot.h"
#include "Piece.h"

class PlayerInput : public cocos2d::Node
{
public:
	static PlayerInput* create(std::vector<Player*> players);
	virtual bool init(std::vector<Player*> players);
	virtual void handleMillInput();
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);

	virtual void setActivePlayer(Player* player);
private:
	bool _isMilling;

	Player* _activePlayer;
	std::vector<Player*> _players;
	Piece* _selectedPiece;

	cocos2d::EventListenerTouchOneByOne* _touchListener;

	virtual void attemptMill(Piece* touchedPiece);
	virtual void handlePieceTouch(Piece* touchedPiece);
	virtual void handleSpotTouch(Spot* touchedSpot);

	virtual bool checkPieceSelectionStage(Piece* piece);
	virtual bool checkSpotSelectionStage(Spot* touchedSpot);
}; 