// FoodGenerator.h

#ifndef __FOOD_GENERATOR_H__
#define __FOOD_GENERATOR_H__

#include "Food.h"

#ifndef NULL
#define NULL 0
#endif // NULL

class FoodGenerator {
   public:
      // Seed the random number generator
      FoodGenerator(double doughnut_prob, double cheese_prob,
                    double carrot_prob, const int *seed = NULL);
      virtual ~FoodGenerator();

      bool nextFoodReady();
      Food getNextFood();

   protected:
      // Return a random number between 0 and 1, selected from a 
      // uniform distribution.
      float getRandomNumber();

      // Returns the probability that food will appear once the
      // buffer has been passed.
      virtual float nextFoodProbability() = 0;

      // Returns the minimum amount of space there must be between foods
      virtual unsigned int getExtraFoodBuffer() = 0;

   private:
      // Selects a food to be returned to the game
      virtual FoodType pickFoodType();

      double p_doughnut;
      double p_cheese;
      double p_carrot;

      unsigned int lastFoodBuffer;
};

#endif // __FOOD_GENERATOR_H__
