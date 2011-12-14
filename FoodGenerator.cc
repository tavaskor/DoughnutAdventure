#include "FoodGenerator.h"

#include "WindowConstants.h"

#include <cstdlib>
#include <ctime>

FoodGenerator::FoodGenerator(double doughnut_prob, double cheese_prob,
                             double carrot_prob, const int *seed) : 
      p_doughnut(doughnut_prob), p_cheese(cheese_prob + doughnut_prob),
      p_carrot(carrot_prob + cheese_prob + doughnut_prob), 
      lastFoodBuffer(0) {
   if (seed == NULL) {
      srand( (unsigned)time( NULL ) );
   } else {
      srand(*seed);
   }
}

FoodGenerator::~FoodGenerator() {}

float FoodGenerator::getRandomNumber() {
   float retVal = (float) rand()/RAND_MAX;
   return retVal;
}

bool FoodGenerator::nextFoodReady() {
   if (lastFoodBuffer > 0) {
      lastFoodBuffer--;
      return false;
   }
   return getRandomNumber() < nextFoodProbability();
}

Food FoodGenerator::getNextFood() {
   Food theFood(WINDOW_WIDTH + 10, 5, this->pickFoodType());
   lastFoodBuffer = theFood.getWidth() + getExtraFoodBuffer();
   return theFood;
}

FoodType FoodGenerator::pickFoodType() {
   float foodSelector = this->getRandomNumber();
   if (foodSelector < p_doughnut) {
      return DOUGHNUT;
   } else if (foodSelector < p_cheese) {
      return CHEESE;
   } else if (foodSelector < p_carrot) {
      return CARROT;
   } else {
      return CELERY;
   }
}

