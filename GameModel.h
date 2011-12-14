// GameModel.h

#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include "ModelBase.h"
#include "Player.h"
#include "Food.h"
#include "FoodGenerator.h"

#include <list>
#include <string>

enum GameDifficulty { EASY, HARD };

class GameModel : public ModelBase {
   public:
      GameModel(Player &pl, std::list<Food> &fdlist);
      virtual ~GameModel();

      // Advance time by one unit.  Once a certain number of units of
      // time have passed, the conveyor belt will move forward by one position.
      void advanceTime();

      // Returns true if the game is over, false otherwise
      bool gameOver();

      // Switch difficulty between easy and hard
      void toggleDifficulty();

      // Explicitly set the difficulty level
      void setDifficulty(GameDifficulty gd);

      // Return the current difficulty setting
      GameDifficulty getDifficulty();


      // Adds this key to the set of pressed down keys
      void setKeyPressed(char key);

      // Removes key from the set of pressed down keys
      void setKeyUnpressed(char key);

      // Get a list of keys pressed down
      std::string getKeysPressed();

      // Set game paused or unpaused
      void togglePaused();
      bool gamePaused();

      static const int GAMEOVER_WEIGHT = 100;
      static const int CONVEYOR_EASY = 10;
      static const int CONVEYOR_HARD = 5;
      static const int MOVE_RESET = 3;

   private:
      void decrementAllTimeCounters();
      void moveConveyorItems();

      void decrementIfNonZero(int &counter);

      // Read keys, take action if necessary
      void checkKeyMoves();
      // With special code to check for jumping
      void checkJumps();

      // Check individual key, returns true if move required
      bool checkMove(char key, int &counter);

      // Check details about jumping for when jump button is pushed
      bool playerOnConveyorBelt();
      int maxJumpHeight();
      int minJumpHeight();
      int maxJumpLength();
      int minJumpLength();

      void checkJumpHeightIncrease();
      void checkJumpHeightDecrease();
      bool jumpButtonPressed();

      int conveyorMoveCounter;
      int upMoveCounter;
      int downMoveCounter;
      int leftMoveCounter;
      int rightMoveCounter;
      int jumpLengthCounter;

      Player &player;
      GameDifficulty currDiff;
      std::list<Food> &foodList;
      bool paused;
      bool currentlyJumping;
      bool jumpHasBeenReleased;

      FoodGenerator *foodgen;
      std::string pressedKeys;
};

#endif // __GAME_MODEL_H__
