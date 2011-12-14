// StartHandler.h
#ifndef __START_HANDLER_H__
#define __START_HANDLER_H__

#include "EventHandler.h"
#include "XData.h"
#include "StartModel.h"

class StartHandler : public EventHandler {
   public:
      StartHandler(XData &xdata, GraphicsDrawer &gd, StartModel &sm);

   protected:
      virtual void handleOtherEvents(XEvent &event);

   private:
      bool mouseInButtonBounds(XEvent &event);
      StartModel &model;
      bool buttonPressedInBounds;
};

#endif // __START_HANDLER_H__
