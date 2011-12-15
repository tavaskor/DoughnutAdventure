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

GameModel::GameModel(Player &pl, 
      list<Food> &fdList) : player(pl), currDiff(EASY), foodList(fdList), paused(false), currentlyJumping(false), jumpHasBeenReleased(true) {

   conveyorMoveCounter = CONVEYOR_EASY;
   upMoveCounter = 0;
   downMoveCounter = 0;
   leftMoveCounter = 0;
   rightMoveCounter = 0;
   jumpLengthCounter = 0;

   foodgen = new EasyFoodGenerator();
   pressedKeys = "";
}

GameModel::~GameModel() {
   delete foodgen;
}

bool GameModel::gameOver() {
   return (player.getWeight() <= GAMEOVER_WEIGHT);
}

void GameModel::toggleDifficulty() {
   delete foodgen;
   currDiff = (currDiff == HARD) ? EASY : GameDifficulty(currDiff+1);
   if (currDiff == HARD) {
      foodgen = new HardFoodGenerator();
   } else {
      foodgen = new EasyFoodGenerator();
   }
}

void GameModel::setDifficulty(GameDifficulty gd) {
   currDiff = gd;
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
      updateAllViews();
   }
   if ( getKeysPressed() != "" ) {
      checkKeyMoves();
   }
   checkJumps();
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

void GameModel::checkKeyMoves() {
   if ( checkMove('i', upMoveCounter) ) {
      // move up?
   } 
   if ( checkMove('j', leftMoveCounter) ) {
      if ( player.getLeftX() > 0 ) {
	 player.increaseX(-BASE_CHANGE_AMT);
      }
   } 
   if ( checkMove('k', rightMoveCounter) ) {
      if ( player.getLeftX() + player.getWidth() < WINDOW_WIDTH ) {
	 player.increaseX(BASE_CHANGE_AMT);
      }
   } 
   if ( checkMove('m', downMoveCounter) ) {
      // move down?
   }
}

bool GameModel::checkMove(char key, int &counter) {
   const string &keyList = this->getKeysPressed();
   string::size_type index = keyList.find(key);

   if ( (index != string::npos) && (counter == 0) ) {
      counter = MOVE_RESET;
      return true;
   }
   return false;
}

bool GameModel::jumpButtonPressed() {
   return ( (this->getKeysPressed()).find(' ') != string::npos );
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



void GameModel::setKeyPressed(char key) {
   pressedKeys += key;
}

void GameModel::setKeyUnpressed(char key) {
   for (unsigned int i = 0; i < pressedKeys.size(); i++) {
      if (pressedKeys.at(i) == key) {
	 pressedKeys.erase(i, 1);
      }
   }
}

std::string GameModel::getKeysPressed() {
   return pressedKeys;
}

void GameModel::togglePaused() {
   paused = !paused;
   updateAllViews();
}

bool GameModel::gamePaused() {
   return paused;
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
