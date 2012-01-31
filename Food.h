// Food.h

#ifndef __FOOD_H__
#define __FOOD_H__

#include "Object.h"

enum FoodType { DOUGHNUT, CARROT, CELERY, CHEESE };

class Food : public Object {
   public:
      static int getMaxFoodHeight();
	  static int getMaxFoodWidth();
	  FoodType getFoodType() const;
	
  	  virtual int getCollissionModifier() const = 0;

   protected:
      Food(int x, int y, int width, int height, FoodType ft);

   private:
      FoodType theFoodType;
};

class Doughnut : public Food {
public:
	Doughnut(int x, int y);
	virtual int getCollissionModifier() const;
};

class Carrot : public Food {
public:
	Carrot(int x, int y);
	virtual int getCollissionModifier() const;
};

class Celery : public Food {
public:
	Celery(int x, int y);
	virtual int getCollissionModifier() const;
};

class Cheese : public Food {
public:
	Cheese(int x, int y);
	virtual int getCollissionModifier() const;
};

#endif // __FOOD_H__
