#pragma once
#include "cocos2d.h"
#include "Spot.h"
#include "Player.h"

class Checker : public cocos2d::Node
{
public:
	static Checker* create(std::vector<Player*> players);
	virtual bool init(std::vector<Player*> players);

	virtual void handlePiecedPlaced(Spot* piecePlacedSpot, Player* currentPlayer);

	virtual void handleOnEndTurn();
	virtual void checkWin(Player* player);

	virtual bool checkForMill(Spot* piecePlacedSpot, Player* currentPlayer);
	virtual bool checkMillFromSpot(Spot* startSpot, Spot* excludeSpot, Player* currentPlayer);
	virtual bool dfs(Spot* startSpot, Spot* currentSpot, Spot* excludeSpot, Player* currentPlayer, std::set<Spot*>& visited, int depth);
	virtual bool checkMiddlePlacing(Spot* startSpot, Player* currentPlayer);

	virtual void throwGameOver(Player* enemyPlayer);
private:
	std::vector<Player*> _players;
};

