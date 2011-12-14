// EasyFoodGenerator.h

#ifndef __EASY_FOOD_GENERATOR_H__
#define __EASY_FOOD_GENERATOR_H__

#include "FoodGenerator.h"
#include "Food.h"

class EasyFoodGenerator : public FoodGenerator {
   public:
      EasyFoodGenerator(const int *seed = NULL);
      virtual ~EasyFoodGenerator();

   protected:
      virtual float nextFoodProbability();
      virtual unsigned int getExtraFoodBuffer();
};

#endif // __EASY_FOOD_GENERATOR_H__
