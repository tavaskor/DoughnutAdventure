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
      virtual void handleOtherEvents(XEvent &event) = 0;

      // Sets which events to check for.  Automatically adds in the Exposure
      // mask, since this base class already handles Exposure events.
      virtual void selectInput(long event_mask);

      XData &xdat;
      GraphicsDrawer &gd;

   private:
      XEvent* getNextEvent();
      bool checkAndHandleExpose(XEvent &theEvent);
      bool checkAndHandleQuit(XEvent &theEvent);
};

#endif // __EVENT_HANDLER_H__
