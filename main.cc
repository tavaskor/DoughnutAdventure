// X headers

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/timeb.h>
#include <list>

#include "XData.h"

#include "SplashHandler.h"
#include "SplashModel.h"
#include "SplashDrawer.h"
#include "StartDrawer.h"
#include "GameOverDrawer.h"

#include "GameHandler.h"
#include "GameModel.h"
#include "GameDrawer.h"


const static unsigned int MILLI_RESOLUTION = 5;

void gameLoop(XData &xdata);
void splashScreenLoop(XData &xdata, bool gameStart);


int main() {
   XData xdata;

   splashScreenLoop(xdata, true);
   while (true) {
      gameLoop(xdata);
      splashScreenLoop(xdata, false);
   }
}

void splashScreenLoop(XData &xdata, bool gameStart) {
   SplashModel model;
   SplashDrawer *drawer;
   if (gameStart) {
       drawer = new StartDrawer(xdata, model);
   } else {
       drawer = new GameOverDrawer(xdata, model);
   }
   SplashHandler handler(xdata, *drawer, model);
   
   while (!model.buttonIsActivated()) {
      handler.handleEvent();
   }
   delete drawer;
}


void loopUntilGameOver(GameModel &model, GameHandler &handler) {
   while (!model.gameOver()) {
      timeb initial, after;
      ftime(&initial);
      
      handler.handleEvent();
      if (!model.gamePaused()) {
         model.advanceTime();
      }
      
      ftime(&after);

      unsigned int milli_adjust = (1000 * (after.time - initial.time)) +
         (after.millitm - initial.millitm);
      if (milli_adjust < MILLI_RESOLUTION) {
         usleep((MILLI_RESOLUTION * 1000) - (milli_adjust * 1000));
      }
   }
}

void gameLoop(XData &xdata) {
   GameModel model;
   GameDrawer draw(xdata, model);
   GameHandler handler(xdata, draw, model);
   loopUntilGameOver(model, handler);
}