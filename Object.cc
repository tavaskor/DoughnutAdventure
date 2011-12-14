#include "Object.h"

Object::Object(int x, int y, int width, int height) : x(x), y(y), w(width), h(height) {}

int Object::getLeftX() const { return x; }
int Object::getBottomY() const { return y; }
int Object::getWidth() const { return w; }
int Object::getHeight() const { return h; }

void Object::increaseX(int amount) { x += amount; }
void Object::increaseY(int amount) { y += amount; }
void Object::increaseWidth(int amount) { w += amount; }


bool Object::collidesWith(Object &other) {
   return ( horizontalCollission(other) && verticalCollission(other) );
}

bool Object::horizontalCollission(Object &other) {
   return ( leftCollission(other) || rightCollission(other) );
}

bool Object::verticalCollission(Object &other) {
   return ( topCollission(other) || bottomCollission(other) );
}

bool Object::leftCollission(Object &other) {
   return ( (x >= other.x) && (x <= other.x + other.w) );
}

bool Object::rightCollission(Object &other) {
   return ( (x + w >= other.x) && (x + w <= other.x + other.w) );
}

bool Object::topCollission(Object &other) {
   return ( (y >= other.y) && (y <= other.y + other.h) );
}

bool Object::bottomCollission(Object &other) {
   return ( (y + h >= other.y) && (y + h <= other.y + other.h) );
}
