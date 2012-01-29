#include "Player.h"

Player::Player() : Object(DEF_X, DEF_Y, DEF_W, DEF_H), weight(START_WEIGHT) {}

void Player::addWeight(int amount) {
   int oldWeight = weight;
   weight += amount;
   this->increaseWidth( (weight / WEIGHT_CHANGE_AMOUNT) -
	 (oldWeight / WEIGHT_CHANGE_AMOUNT) );
}

int Player::getWeight() const {
   return weight;
}

void Player::setMoving(MoveType type, bool state) {
	currentMoves[type] = state;
}

bool Player::isMoving(MoveType type) const {
	std::map<MoveType, bool>::const_iterator it;
	it = currentMoves.find(type);
	return (it == currentMoves.end()) ? false : it->second;
}