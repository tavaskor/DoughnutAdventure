#include "Player.h"
#include "Object.h"

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
