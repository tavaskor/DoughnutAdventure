// X headers

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sys/timeb.h>

#include "XData.h"
#include "StartHandler.h"
#include "StartDrawer.h"
#include "StartModel.h"
#include "GameHandler.h"
#include "GameDrawer.h"
#include "GameModel.h"
#include "Player.h"
#include "Food.h"
#include "GameOverDrawer.h"

#include <list>

void startScreenLoop(XData &xdata);
void gameLoop(XData &xdata);
void gameOverLoop(XData &xdata);

void checkEvents(XData &xdata, GameHandler &handler); 

int main() {
   XData xdata;

   startScreenLoop(xdata);
   while (true) {
      gameLoop(xdata);
      gameOverLoop(xdata);
   }
}


void startScreenLoop(XData &xdata) {
   StartModel model;
   StartDrawer draw(xdata, model);
   StartHandler handler(xdata, draw, model);
   while (!model.buttonIsActivated()) {
      handler.handleEvent();
   }
}

void gameOverLoop(XData &xdata) {
   StartModel model;
   GameOverDrawer draw(xdata, model);
   StartHandler handler(xdata, draw, model);
   while (!model.buttonIsActivated()) {
      handler.handleEvent();
   }
}

void gameLoop(XData &xdata) {
   const static unsigned int MILLI_RESOLUTION = 5;
   std::list<Food> fl;
   Player homer;
   GameModel model(homer, fl);
   GameDrawer draw(xdata, model, homer, fl);
   GameHandler handler(xdata, draw, model);
   while (!model.gameOver()) {
      timeb initial, after;
      ftime(&initial);
      checkEvents(xdata, handler);
      if (!model.gamePaused()) {
         model.advanceTime();
         // Repaint if necessary
      }
      ftime(&after);

      unsigned int milli_adjust = (1000 * (after.time - initial.time)) +
         (after.millitm - initial.millitm);
      if (milli_adjust < MILLI_RESOLUTION) {
         usleep((MILLI_RESOLUTION * 1000) - (milli_adjust * 1000));
      }
   }
}

void checkEvents(XData &xdata, GameHandler &handler) {
   if ( XPending(xdata.display) ) {
      handler.handleEvent();
   }
}
