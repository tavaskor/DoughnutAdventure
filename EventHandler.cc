#include "EventHandler.h"

#include <X11/Xlib.h>
#include <iostream>  // For exit call; seems unnecessarily bulky

void EventHandler::selectInput(long event_mask) {
    xdat.selectInput(ExposureMask | KeyPressMask | event_mask);
}

void EventHandler::handleEvent() {
   if ( xdat.pending() ) {
       XEvent *xe = xdat.getNextEvent();
       if (!checkAndHandleExpose(*xe) && !checkAndHandleQuit(*xe)) {
          handleOtherEvents(*xe);
       }
       delete xe;
   }
}

bool EventHandler::checkAndHandleExpose(XEvent &theEvent) {
   if (theEvent.type == Expose) {
      gd.redraw();
      return true;
   }
   return false;
}

bool EventHandler::checkAndHandleQuit(XEvent &theEvent) {
   if (theEvent.type == KeyPress) {
      KeySym key;
      const int BUFFER_SIZE = 10;
      char text[BUFFER_SIZE];

      int i = XLookupString( (XKeyEvent *) &theEvent, text, BUFFER_SIZE,
	    &key, 0);
      if ( i == 1 && ( text[0] == 'q' || text[0] == 'Q' ) ) {
	 // Exit the program!
         xdat.finalCleanup();
	 exit(0);
      }
   }
   return false;
}
