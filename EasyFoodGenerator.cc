#include "EasyFoodGenerator.h"
#include "Food.h"

EasyFoodGenerator::EasyFoodGenerator(const int *seed) : 
    FoodGenerator(.4, .25, .2, seed) {}

EasyFoodGenerator::~EasyFoodGenerator() {}
float EasyFoodGenerator::nextFoodProbability() { return .12; }
unsigned int EasyFoodGenerator::getExtraFoodBuffer() { return 5; }
