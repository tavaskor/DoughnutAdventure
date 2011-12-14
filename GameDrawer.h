// GameDrawer.h

#ifndef __GAME_DRAWER_H__
#define __GAME_DRAWER_H__

#include "GraphicsDrawer.h"
#include "GameModel.h"
#include "Player.h"
#include "Food.h"

#include <list>

class GameDrawer : public GraphicsDrawer {
   public:
      GameDrawer(XData &xdata, GameModel &gm, Player &pl, std::list<Food> &fdList);
      virtual void redraw();

   private:
      void drawPlayer();
      void drawFood();
      void drawConveyorBelt();
      void drawStatusBar();
      void drawPaused();

      void drawDoughnut(const Object &doughnut);
      void drawCarrot(const Object &carrot);
      void drawCelery(const Object &celery);
      void drawCheese(const Object &cheese);

      void drawRectangle(int x, int y, int width, int height);
      void fillRectangle(int x, int y, int width, int height);
      void drawEllipse(int centreX, int centreY, int width, int height);
      void fillEllipse(int centreX, int centreY, int width, int height);
      void drawLine(int x1, int y1, int x2, int y2);

      GameModel &model;
      Player &player;
      std::list<Food> &foodList;
};

#endif // __GAME_DRAWER_H__
