#include "GameHandler.h"
#include "Player.h"

#include <X11/X.h> 


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
		 case 'p':
			model.togglePaused();
			break;
		 case 'j':
			  model.getPlayer().setMoving(LEFT_MOVE, true);
			break;
		 case 'k':
			model.getPlayer().setMoving(RIGHT_MOVE, true);
			break;
		 case ' ':
			model.getPlayer().setMoving(JUMP, true);
			break;
      }
   } else if (eventType == KeyRelease) {
	   switch(pressedKey) {
		   case 'j':
			   model.getPlayer().setMoving(LEFT_MOVE, false);
			   break;
		   case 'k':
			   model.getPlayer().setMoving(RIGHT_MOVE, false);
			   break;
		   case ' ':
			   model.getPlayer().setMoving(JUMP, false);
			   break;
	   }
   }
}
