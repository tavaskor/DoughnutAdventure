// StartHandler.h
#ifndef __SPLASH_HANDLER_H__
#define __SPLASH_HANDLER_H__

#include "EventHandler.h"
#include "XData.h"
#include "SplashModel.h"

class SplashHandler : public EventHandler {
   public:
      SplashHandler(XData &xdata, GraphicsDrawer &gd, SplashModel &sm);

   protected:
      virtual void handleOtherEvents(XEvent &event);

   private:
      bool mouseInButtonBounds(XEvent &event);
      SplashModel &model;
      bool buttonPressedInBounds;
};

#endif // __SPLASH_HANDLER_H__
