#include "SplashHandler.h"

#include <X11/X.h>

SplashHandler::SplashHandler(XData &xdata, GraphicsDrawer &graphdraw,
      SplashModel &sm) : EventHandler(xdata, graphdraw), model(sm) {
//   XAutoRepeatOn(xdata.display); // Was there a reason for this here?
}

void SplashHandler::handleOtherEvents(int eventType) {
   // We need to check if "start" is pressed
   switch(eventType) {
      case ButtonPress:
	 if ( mouseInButtonBounds() ) {
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
	    if ( model.isButtonPressed() && !mouseInButtonBounds() ) {
	       model.setButtonUnpressed();
	    } else if ( !model.isButtonPressed() && mouseInButtonBounds() ) {
	       model.setButtonPressed();
	    }
         }
         break;
   }
}

bool SplashHandler::mouseInButtonBounds() {
   int mousex = xdat.getMouseX();
   int mousey = xdat.getMouseY();
   return mousex >= model.getButtonX() && mousey >= model.getButtonY() &&
      mousex <= model.getButtonX() + model.getButtonWidth() &&
      mousey <= model.getButtonY() + model.getButtonHeight();
}
