#include "EventHandler.h"

#include <X11/X.h>
#include <cstdlib>

void EventHandler::handleEvent() {
   int event = xdat.eventPending();
   if (event && !checkAndHandleExpose(event) && !checkAndHandleQuit(event)) {
      handleOtherEvents(event);
   }
}

bool EventHandler::checkAndHandleExpose(int eventType) {
   if (eventType == Expose) {
      gd.redraw();
      return true;
   }
   return false;
}

bool EventHandler::checkAndHandleQuit(int eventType) {
   if ((eventType == KeyPress) && (xdat.getPressedKey() == 'q')) {
      // Exit the program!
      xdat.finalCleanup();
      exit(0);
   }
   return false;
}
