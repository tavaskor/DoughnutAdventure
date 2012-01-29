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
      GameModel();
      virtual ~GameModel();

      // Advance time by one unit.  Once a certain number of units of
      // time have passed, the conveyor belt will move forward by one position.
      void advanceTime();

      // Returns true if the game is over, false otherwise
      bool gameOver() const;

      // Explicitly set the difficulty level
      void setDifficulty(GameDifficulty gd);

      // Return the current difficulty setting
      GameDifficulty getDifficulty();


      // Set game paused or unpaused
      void togglePaused();
      bool gamePaused();
      
      // Access state for the purposes of the view, set state for the controller.
      Player& getPlayer();
      const std::list<Food>& getFoodList() const;

      static const int GAMEOVER_WEIGHT = 100;
      static const int CONVEYOR_EASY = 5;
      static const int CONVEYOR_HARD = 3;
	
   private:
      void decrementAllTimeCounters();
      void moveConveyorItems();

      void decrementIfNonZero(int &counter);

	  // See if the player is currently moving; updated positioning if so.
      void checkDirectionMoves();
      void checkJumps();

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

      Player player;
      GameDifficulty currDiff;
      std::list<Food> foodList;
      bool paused;
      bool currentlyJumping;
      bool jumpHasBeenReleased;

      FoodGenerator *foodgen;
};

#endif // __GAME_MODEL_H__
