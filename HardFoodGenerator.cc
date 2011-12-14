#include "HardFoodGenerator.h"

HardFoodGenerator::HardFoodGenerator(const int *seed) : 
    FoodGenerator(.2, .25, .25, seed) {}

HardFoodGenerator::~HardFoodGenerator() {}
float HardFoodGenerator::nextFoodProbability() { return .32; }
unsigned int HardFoodGenerator::getExtraFoodBuffer() { return 0; }
