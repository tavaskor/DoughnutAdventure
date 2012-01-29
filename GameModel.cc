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
   delete foodgen;
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
   bool doneLoop = false;
   bool forLoopBreak = false;
   while (!doneLoop) {
      for (list<Food>::iterator iter = foodList.begin(); iter != foodList.end();
	    iter++) {
	 iter->increaseX(-BASE_CHANGE_AMT);
	 if ( player.collidesWith(*iter) ) {
	    player.addWeight( iter->getCollissionModifier() );
	    foodList.erase(iter);
	    updateAllViews();

	    // Iterator is no longer valid, so need to restart the for loop.
	    // Reason: could potentially collide with >1 food, so need to
	    // check everything.
	    forLoopBreak = true;
	    break;
	 }
      }
      if ( forLoopBreak == true ) {
	 forLoopBreak = false;
      } else {
	 doneLoop = true;
      }
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

const std::list<Food>& GameModel::getFoodList() const {
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

void GameModel::checkJumpHeightDecrease() {
   if ( player.getBottomY() == maxJumpHeight() && jumpLengthCounter == 0) {
      currentlyJumping = false;
   }

   if ( !playerOnConveyorBelt() && ( jumpHasBeenReleased || !jumpButtonPressed() || (!currentlyJumping && jumpLengthCounter == 0) ) ) {
      player.increaseY(-2 * BASE_CHANGE_AMT);
      if ( player.getBottomY() <= 5 ) {
	 int yChange = 5 - player.getBottomY();
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
   return Food::getHeight(CARROT) + 6;
}

int GameModel::minJumpLength() {
   return 50;
}

int GameModel::maxJumpHeight() {
   int retVal = 150 - ( player.getWeight() / 2 );
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
   return ( player.getBottomY() == 5 );
}
