#include "Checker.h"

Checker* Checker::create(std::vector<Player*> players) {
    Checker* checker = new (std::nothrow) Checker();
    if (checker && checker->init(players)) {
        checker->autorelease();
        return checker;
    }
    CC_SAFE_DELETE(checker);
    return nullptr;
}

bool Checker::init(std::vector<Player*> players)
{
    _players = players;
	auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();
	auto playerInputFinishedListener = cocos2d::EventListenerCustom::create("player_placed_piece", [&](cocos2d::EventCustom* e) {
		Piece* touchedPiece = static_cast<Piece*>(e->getUserData());
        Spot* touchedSpot = dynamic_cast<Spot*>(touchedPiece->getParent());
        Player* owner;
        for each (Player * player in _players) {
            if (player->isPlayerPiece(touchedPiece)) {
                owner = player;
            }
        }
		handlePiecedPlaced(touchedSpot, owner);
		});

	dispatcher->addEventListenerWithSceneGraphPriority(playerInputFinishedListener, this);

    auto playerEndTurnListener = cocos2d::EventListenerCustom::create("end_turn", [&](cocos2d::EventCustom* e) {
        handleOnEndTurn();
        });
    dispatcher->addEventListenerWithSceneGraphPriority(playerEndTurnListener, this);

	return true;
}

bool Checker::checkForMill(Spot* piecePlacedSpot, Player* currentPlayer) {
    std::vector<Spot*> connectingSpots = piecePlacedSpot->getConnectingSpots();

    for (Spot* spot : connectingSpots) {
        if (spot->isOccupied() && currentPlayer->isPlayerPiece(spot->getOccupyingPiece())) {
            if (checkMiddlePlacing(piecePlacedSpot, currentPlayer) || checkMillFromSpot(piecePlacedSpot, spot, currentPlayer)) {
                return true; 
            }
        }
    }

    return checkMillFromSpot(piecePlacedSpot, nullptr, currentPlayer);
}

bool Checker::checkMillFromSpot(Spot* startSpot, Spot* excludeSpot, Player* currentPlayer) {
    std::set<Spot*> visited;
    return dfs(startSpot, startSpot, excludeSpot, currentPlayer, visited, 1);
}

bool Checker::dfs(Spot* startSpot, Spot* currentSpot, Spot* excludeSpot, Player* currentPlayer, std::set<Spot*>& visited, int depth) {
    if (currentSpot == excludeSpot) {
        return false; // Skip this spot if it's excluded
    }

    Piece* occupyingPiece = currentSpot->getOccupyingPiece();
    if (occupyingPiece && currentPlayer->isPlayerPiece(occupyingPiece) && (currentSpot->getPosition().y == startSpot->getPosition().y || currentSpot->getPosition().x == startSpot->getPosition().x)) {
        if (depth == 3) {
            return true; // Mill formed
        }
        else {
            visited.insert(currentSpot); // Mark current spot as visited
            std::vector<Spot*> connectingSpots = currentSpot->getConnectingSpots();
            for (Spot* nextSpot : connectingSpots) {
                if (visited.find(nextSpot) == visited.end()) {
                    if (dfs(startSpot, nextSpot, excludeSpot, currentPlayer, visited, depth + 1)) {
                        return true; // Mill formed in deeper level
                    }
                }
            }
            visited.erase(currentSpot); // Remove current spot from visited set before returning
        }
    }
    return false; // Mill not formed
}

bool Checker::checkMiddlePlacing(Spot* startSpot, Player* currentPlayer) {
    int horisontalCounter = 0;
    int verticalCounter = 0;

    for each (Spot * spot in startSpot->getConnectingSpots()) {
        if (!spot->getOccupyingPiece() || !currentPlayer->isPlayerPiece(spot->getOccupyingPiece())) continue;

        if (spot->getPosition().x == startSpot->getPosition().x) {
            horisontalCounter++;
        }
        if (spot->getPosition().y == startSpot->getPosition().y) {
            verticalCounter++;
        }
    }

    return horisontalCounter == 2 || verticalCounter == 2;
}

void Checker::handlePiecedPlaced(Spot* piecePlacedSpot, Player* currentPlayer) {
	auto dispatcher = cocos2d::Director::getInstance()->getEventDispatcher();

	if (checkForMill(piecePlacedSpot, currentPlayer)) {
		dispatcher->dispatchCustomEvent("player_achieved_mill");
	}
	else {
		dispatcher->dispatchCustomEvent("player_no_mill");
	}
}

void Checker::handleOnEndTurn() {
    for each (Player * player in _players) {
        checkWin(player);
    }
}

void Checker::checkWin(Player* enemyPlayer) {
    if (enemyPlayer->getPieces().size() <= 2) {
        throwGameOver(enemyPlayer);
        return;
    }
    else {
        for each (Piece * piece in enemyPlayer->getPieces()) {
            Spot* spot = dynamic_cast<Spot*>(piece->getParent());
            if (spot != nullptr) {
                for each (Spot * connectingSpot in spot->getConnectingSpots()) {
                    if (connectingSpot->getOccupyingPiece() == nullptr) {
                        return;
                    }
                }
            }
            else return;
        }
    }

    throwGameOver(enemyPlayer);

}

void Checker::throwGameOver(Player* enemyPlayer) {
    for each (Player * player in _players) {
        if(player != enemyPlayer) cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("game_over", player);
    }
}