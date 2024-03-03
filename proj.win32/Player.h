#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Piece.h"

class Player : public cocos2d::Node
{
public:
	static Player* create(std::string playerName, cocos2d::Color4B playerColor);
	virtual bool init(std::string playerName, cocos2d::Color4B playerColor);

	virtual void setPlayerName(std::string playerName);
	virtual std::string getName();
	virtual void setupNameTextFields(cocos2d::Vec2 anchorPoint, Node* board, int boardPositionX, int boardPositionY);
	virtual void nameTextFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);

	virtual cocos2d::Color4B getColor();

	virtual void setupPieces(int amount, int minOrMaxMulti, std::string spriteFileName, std::string spriteSelectdFileName, Node* board, int boardPositionX, int boardPositionY);
	virtual void addPieceToPlayer(Piece* piece);
	virtual void removePieceToPlayer(Piece* piece);
	virtual bool isPlayerPiece(Piece* piece);
	virtual bool isAllPiecesPlaced();
	virtual std::vector<Piece*> getPieces();
private:
	std::string _name;
	cocos2d::Color4B _playerColor;
	std::vector<Piece*> _pieces;
};