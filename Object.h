// Object.h

/* Base class for all objects in the game.  They know their own positions,
 * and whether they will collide with other objects
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

class Object {
   public:
      Object(int x, int y, int width, int height);

      int getLeftX() const;
      int getBottomY() const;
      int getWidth() const;
      int getHeight() const;

      bool collidesWith(Object &other);

      void increaseX(int amount); // negative to decrease X
      void increaseY(int amount); // negative to decrease Y
      void increaseWidth(int amount);

   private:
      bool horizontalCollission(Object &other);
      bool verticalCollission(Object &other);
      bool leftCollission(Object &other);
      bool rightCollission(Object &other);
      bool topCollission(Object &other);
      bool bottomCollission(Object &other);

      int x;
      int y;
      int w;
      int h;
};

#endif // __OBJECT_H__
