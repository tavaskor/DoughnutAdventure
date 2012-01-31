#include "GameModel.h"
#include "EasyFoodGenerator.h"
#include "HardFoodGenerator.h"
#include "Food.h"
#include "WindowConstants.h"

#include <list>
#include <string>
using std::list;
using std::string;

const static int BASE_CHANGE_AMT = 4;

GameModel::GameModel() : 
        currDiff(EASY), paused(false), currentlyJumping(false), jumpHasBeenReleased(true) {
   conveyorMoveCounter = CONVEYOR_EASY;
   upMoveCounter = 0;
   downMoveCounter = 0;
   leftMoveCounter = 0;
   rightMoveCounter = 0;
   jumpLengthCounter = 0;

   foodgen = new EasyFoodGenerator();
}

GameModel::~GameModel() {
	// There will be one active FoodGenerator; make sure its memory is reclaimed.
	delete foodgen;
	
	// It is also necessary to remove any remaining food items that are still on
	// the conveyor belt at the end of the game.
	for (std::list<Food*>::iterator it = foodList.begin(); it != foodList.end(); it++) {
		delete *it;
	}
}

bool GameModel::gameOver() const {
   return (player.getWeight() <= GAMEOVER_WEIGHT);
}


void GameModel::setDifficulty(GameDifficulty gd) {
   currDiff = gd;
   
   delete foodgen;
   if (currDiff == HARD) {
      foodgen = new HardFoodGenerator();
   } else {
      foodgen = new EasyFoodGenerator();
   }
   
   updateAllViews();
}

GameDifficulty GameModel::getDifficulty() {
   return currDiff;
}


void GameModel::advanceTime() {
   decrementAllTimeCounters();
	
   if ( conveyorMoveCounter == 0 ) {
      moveConveyorItems();
      if ( foodgen->nextFoodReady() ) {
		  foodList.push_back(foodgen->getNextFood());
      }
      if ( this->getDifficulty() == HARD ) {
		  conveyorMoveCounter = CONVEYOR_HARD;
      } else {
		  conveyorMoveCounter = CONVEYOR_EASY;
      }
   }
	
	checkDirectionMoves();
	checkJumps();
	updateAllViews();
}

void GameModel::decrementAllTimeCounters() {
   conveyorMoveCounter--;
   decrementIfNonZero(upMoveCounter);
   decrementIfNonZero(downMoveCounter);
   decrementIfNonZero(leftMoveCounter);
   decrementIfNonZero(rightMoveCounter);
   decrementIfNonZero(jumpLengthCounter);
}

void GameModel::decrementIfNonZero(int &counter) {
   if (counter != 0) {
      counter--;
   }
}

void GameModel::checkDirectionMoves() {
   if ( player.isMoving(LEFT_MOVE) ) {
      if ( player.getLeftX() > 0 ) {
	 player.increaseX(-BASE_CHANGE_AMT);
      }
   } 
   if ( player.isMoving(RIGHT_MOVE) ) {
      if ( player.getLeftX() + player.getWidth() < WINDOW_WIDTH ) {
	 player.increaseX(BASE_CHANGE_AMT);
      }
   }
}

bool GameModel::jumpButtonPressed() {
	return player.isMoving(JUMP);
}

void GameModel::moveConveyorItems() {
	// If the player is on the conveyor belt, move it first; before checking collissions,
	// each food will also be moved.
	if (this->playerOnConveyorBelt()) {
		player.increaseX(-BASE_CHANGE_AMT);
	}
	
	list<Food*>::iterator foodCheck = foodList.begin();
	while (foodCheck != foodList.end()) {
		(*foodCheck)->increaseX(-BASE_CHANGE_AMT);
		if ( player.collidesWith(**foodCheck) ) {
			// Add/remove weight based on the food.
			player.addWeight( (*foodCheck)->getCollissionModifier() );
			
			// Delete the heap-allocated storage, and then remove the pointer
			// from the food list.
			delete (*foodCheck);
			foodCheck = foodList.erase(foodCheck);
		} else {
			foodCheck++;
		}
	}
	
	// Remove any food that has fallen off the edge.
	Food *frontFood = *(foodList.begin());
	if ((!foodList.empty()) && (frontFood->getLeftX() < 0 - frontFood->getWidth())) {
		delete frontFood;
		foodList.erase(foodList.begin());
	}
}


void GameModel::togglePaused() {
   paused = !paused;
   updateAllViews();
}

bool GameModel::gamePaused() {
   return paused;
}

Player& GameModel::getPlayer() {
    return player;
}

const std::list<Food*>& GameModel::getFoodList() const {
    return foodList;
}



void GameModel::checkJumps() {
   checkJumpHeightIncrease();
   checkJumpHeightDecrease();
}


void GameModel::checkJumpHeightIncrease() {
   if ( jumpButtonPressed() && playerOnConveyorBelt() && jumpHasBeenReleased ) {
      currentlyJumping = true;
      jumpHasBeenReleased = false;
   }

   if ( !jumpHasBeenReleased && player.getBottomY() <= maxJumpHeight() && currentlyJumping ) {
      if ( player.getBottomY() != maxJumpHeight() ) {
	 player.increaseY(2 * BASE_CHANGE_AMT);
	 if ( player.getBottomY() >= maxJumpHeight() ) {
	    int yChange = maxJumpHeight() - player.getBottomY();
	    player.increaseY(yChange);
	    jumpLengthCounter = maxJumpLength();
	 }
      }
   }
}


// The lowest the player can go without hitting the conveyor belt.
const static int MIN_PLAYER_Y = 5;

void GameModel::checkJumpHeightDecrease() {
   if ( player.getBottomY() == maxJumpHeight() && jumpLengthCounter == 0) {
      currentlyJumping = false;
   }

   if ( !playerOnConveyorBelt() && ( jumpHasBeenReleased || !jumpButtonPressed() || (!currentlyJumping && jumpLengthCounter == 0) ) ) {
      player.increaseY(-2 * BASE_CHANGE_AMT);
	   
	  // If the player is below the conveyor belt, put the player properly on the
	  // conveyor belt.
      if ( player.getBottomY() <= MIN_PLAYER_Y ) {
		  int yChange = MIN_PLAYER_Y - player.getBottomY();
		  player.increaseY(yChange);
		  currentlyJumping = false;
      }
   }
   
   // Need to reset jumpHasBeenReleased *somewhere*...
   if (!jumpButtonPressed()) {
      jumpHasBeenReleased = true;
   }
}

int GameModel::minJumpHeight() {
	return Food::getMaxFoodHeight() + 6;
}

int GameModel::minJumpLength() {
   return 50;
}

int GameModel::maxJumpHeight() {
   int retVal = 300 - player.getWeight();
   if ( retVal > minJumpHeight() ) {
      return retVal;
   }
   return minJumpHeight();
}

int GameModel::maxJumpLength() {
   int retVal = (760 - (player.getWeight() * 2)) / BASE_CHANGE_AMT;
   if ( retVal > minJumpLength() ) {
      return retVal;
   }
   return minJumpLength();
}

bool GameModel::playerOnConveyorBelt() {
   return ( player.getBottomY() == MIN_PLAYER_Y );
}
