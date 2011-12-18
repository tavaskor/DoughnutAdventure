// GameHandler.h

#ifndef __GAME_HANDLER_H__
#define __GAME_HANDLER_H__

#include "EventHandler.h"
#include "GraphicsDrawer.h"
#include "GameModel.h"

class GameHandler : public EventHandler {
   public:
      GameHandler(XData &xdata, GraphicsDrawer &gd, GameModel &gm);

   protected:
      virtual void handleOtherEvents(int eventType);

   private:
      GameModel &model;
};

#endif // __GAME_HANDLER_H__
