#include "PlayerTextFieldDelegate.h"

void PlayerTextFieldDelegate::setPlayer(Player* player) {
	_player = player;
}

bool PlayerTextFieldDelegate::onTextFieldDetachWithIME(cocos2d::TextFieldTTF* sender) {
	_player->setName(sender->getString());
	return false;
}