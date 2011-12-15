// GameOverDrawer.h

#ifndef __GAME_OVER_DRAWER_H__
#define __GAME_OVER_DRAWER_H__

#include "SplashDrawer.h"
#include "SplashModel.h"

class GameOverDrawer : public SplashDrawer {
   public:
      GameOverDrawer(XData &xdata, SplashModel &sm);

   protected:
      virtual const char* getHeader();
      virtual const char* getInstruction();
};

#endif // __GAME_OVER_DRAWER_H__
