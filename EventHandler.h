// EventHandler.h
#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "XData.h"
#include "GraphicsDrawer.h"

class EventHandler {
   // Note: subclasses should call selectinput to set up appropriate
   // event checking

   public:
      virtual void handleEvent();
      virtual ~EventHandler() {}

   protected:
      EventHandler(XData &xdata, GraphicsDrawer &graphdraw) : xdat(xdata),
							      gd(graphdraw) {}
      virtual void handleOtherEvents(int eventType) = 0;

      XData &xdat;
      GraphicsDrawer &gd;

   private:
      bool checkAndHandleExpose(int eventType);
      bool checkAndHandleQuit(int eventType);
};

#endif // __EVENT_HANDLER_H__
