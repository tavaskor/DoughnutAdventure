#include "GameHandler.h"

#include <X11/X.h> 
#include <iostream>
using std::cerr;
using std::endl;

GameHandler::GameHandler(XData &xdata, GraphicsDrawer &graphdraw, 
      GameModel &gm) : EventHandler(xdata, graphdraw), model(gm) {}

void GameHandler::handleOtherEvents(int eventType) {
   const char pressedKey = xdat.getPressedKey();

   if (eventType == KeyPress) {
      switch(pressedKey) {
         case '1':
            model.setDifficulty(EASY);
            break;
         case '2':
            model.setDifficulty(HARD);
            break;
         default:
            model.setKeyPressed(pressedKey);
      }
   } else if (eventType == KeyRelease) {
      model.setKeyUnpressed(pressedKey);
   }
}
