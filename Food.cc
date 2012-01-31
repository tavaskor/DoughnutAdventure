#include "Food.h"

Food::Food(int x, int y, int width, int height,
      FoodType ft) : Object(x, y, width, height), theFoodType(ft) {}

Doughnut::Doughnut(int x, int y) : Food(x, y, 25, 25, DOUGHNUT) {}
Celery::Celery(int x, int y) : Food(x, y, 25, 15, CELERY) {}
Carrot::Carrot(int x, int y) : Food(x, y, 20, 30, CARROT) {}
Cheese::Cheese(int x, int y) : Food(x, y, 22, 22, CHEESE) {}

int Food::getMaxFoodHeight() { return 30; }
int Food::getMaxFoodWidth() { return 25; }

int Doughnut::getCollissionModifier() const { return 5; }
int Carrot::getCollissionModifier() const { return -7; }
int Celery::getCollissionModifier() const { return -10; }
int Cheese::getCollissionModifier() const { return -3; }

FoodType Food::getFoodType() const { return theFoodType; }