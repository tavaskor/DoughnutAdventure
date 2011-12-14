#include "StartHandler.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

StartHandler::StartHandler(XData &xdata, GraphicsDrawer &graphdraw,
      StartModel &sm) : EventHandler(xdata, graphdraw), model(sm) {
   this->selectInput( ButtonPressMask | ButtonReleaseMask | 
	 ButtonMotionMask );
   XAutoRepeatOn(xdata.display);
}

void StartHandler::handleOtherEvents(XEvent &event) {
   // We need to check if "start" is pressed
   switch(event.type) {
      case ButtonPress:
	 if ( mouseInButtonBounds(event) ) {
	    model.setButtonPressed();
	    buttonPressedInBounds = true;
	 } else {
	    buttonPressedInBounds = false;
	 }
	 break;
      case ButtonRelease:
	 if ( model.isButtonPressed() ) {
	    // The start button has been pressed correctly!  Continue on.
	    model.setButtonActivated();
	 }
	 break;
      case MotionNotify:
	 if (buttonPressedInBounds) {
	    // The button was pressed in bounds, but the pointer may have
	    // been moved in and out of the start button.  If so, the model
	    // needs to be updated accordingly.
	    if ( model.isButtonPressed() && !mouseInButtonBounds(event) ) {
	       model.setButtonUnpressed();
	    } else if ( !model.isButtonPressed() && mouseInButtonBounds(event) ) {
	       model.setButtonPressed();
	    }
	 }
	 break;
   }
}

bool StartHandler::mouseInButtonBounds(XEvent &event) {
   int mousex = event.xbutton.x;
   int mousey = event.xbutton.y;
   return mousex >= model.getButtonX() && mousey >= model.getButtonY() &&
      mousex <= model.getButtonX() + model.getButtonWidth() &&
      mousey <= model.getButtonY() + model.getButtonHeight();
}
