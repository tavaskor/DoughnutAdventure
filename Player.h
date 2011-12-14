// Player.h

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.h"

class Player : public Object {
   public:
      Player();

      void addWeight(int amount);
      int getWeight();

      static const int START_WEIGHT = 150;
      static const int DEF_X = 0;
      static const int DEF_Y = 5;
      static const int DEF_W = 20;
      static const int DEF_H = 40;
      
      // how much triggers change in character's size
      static const int WEIGHT_CHANGE_AMOUNT = 5; 

   private:
      int weight;
};

#endif // __PLAYER_H__
