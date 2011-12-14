// Food.h

#ifndef __FOOD_H__
#define __FOOD_H__

#include "Object.h"

enum FoodType { DOUGHNUT, CARROT, CELERY, CHEESE };
const int NUM_FOOD_TYPES = 4;


class Food : public Object {
   public:
      static int getHeight(FoodType ft);
      static int getWidth(FoodType ft);

      Food(int x, int y, FoodType ft);
      FoodType getFoodType() const;
      int getCollissionModifier() const;
      int getHeight() const;
      int getWidth() const;

   private:
      FoodType theFoodType;
};

#endif // __FOOD_H__
