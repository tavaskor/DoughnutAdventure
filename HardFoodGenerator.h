// HardFoodGenerator.h

#ifndef __HARD_FOOD_GENERATOR_H__
#define __HARD_FOOD_GENERATOR_H__

#include "FoodGenerator.h"
#include "Food.h"

class HardFoodGenerator : public FoodGenerator {
   public:
      HardFoodGenerator(const int *seed = NULL);
      virtual ~HardFoodGenerator();

   protected:
      virtual float nextFoodProbability();
      virtual unsigned int getExtraFoodBuffer();
};

#endif // __HARD_FOOD_GENERATOR_H__
