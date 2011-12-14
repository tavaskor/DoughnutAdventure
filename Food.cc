#include "Food.h"

Food::Food(int x, int y, 
      FoodType ft) : Object(x, y, getWidth(ft), getHeight(ft)), theFoodType(ft) {}

FoodType Food::getFoodType() const { return theFoodType; }
int Food::getHeight() const { return getHeight(theFoodType); }
int Food::getWidth() const { return getWidth(theFoodType); }

int Food::getHeight(FoodType ft) {
   switch (ft) {
      case DOUGHNUT:
	 return 25;
      case CARROT:
	 return 30;
      case CELERY:
	 return 15;
      case CHEESE:
	 return 22;
      default:
	 return -1;
   }
}

int Food::getWidth(FoodType ft) {
   switch (ft) {
      case DOUGHNUT:
	 return 25;
      case CARROT:
	 return 20;
      case CELERY:
	 return 25;
      case CHEESE:
	 return 22;
      default:
	 return -1;
   }
}

int Food::getCollissionModifier() const {
   switch(theFoodType) {
      case DOUGHNUT:
	 return 5;
      case CARROT:
	 return -7;
      case CELERY:
	 return -10;
      case CHEESE:
	 return -3;
      default:
	 return 0;
   }
}
