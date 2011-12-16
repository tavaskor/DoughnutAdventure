#include "SplashDrawer.h"
#include "WindowConstants.h"

#include <string>
using std::string;

SplashDrawer::SplashDrawer(XData &xdata, SplashModel &sm) :
        GraphicsDrawer(xdata), model(sm) {
   model.addView(*this);
}


void SplashDrawer::redraw() {
   XClearWindow( xdat.display, xdat.window );
   drawHeadingInformation();
   drawImmediateInstructions();
   drawGameText();
   drawStartButton();
   XFlush(xdat.display);
}

void SplashDrawer::drawHeadingInformation() {
   xdat.setFont("-*-helvetica-*-o-*-*-34-*-*-*-*-*-*-*");

   const char *title = this->getHeader();
   xdat.drawString(title, 50, CENTRE);
}

void SplashDrawer::drawImmediateInstructions() {
   xdat.setFont("-*-helvetica-*-r-*-*-17-*-*-*-*-*-*-*");

   const char *title = this->getInstruction();
   xdat.drawString(title, 90, CENTRE);
}


void SplashDrawer::drawGameText() {
    xdat.setFont("-*-helvetica-*-r-*-*-12-*-*-*-*-*-*-*");

   const int NUM_STRINGS = 6;
   string *lines = new string[NUM_STRINGS];
   lines[0] = "Game play instructions:";
   lines[1] = "Press j and k to move left and right.  Press spacebar to jump.";
   lines[2] = "Press 1 to set the difficulty to easy or 2 to set the difficulty to hard.";
   lines[3] = "Press p to pause, or q to quit at any time.";
   lines[4] = "The game ends when your weight drops below 100 pounds.";
   lines[5] = "Doughnuts increase your weight; all other foods decrease it.";

   for (int i = 0; i < NUM_STRINGS; i++) {
      const char* label = lines[i].c_str();
      xdat.drawString(label, 130 + (20 * i), CENTRE);
   }
}


void SplashDrawer::drawStartButton() {
   if ( model.isButtonPressed() ) {
      XFillRectangle(xdat.display, xdat.window, xdat.gc,
	    model.getButtonX(), model.getButtonY(),
	    model.getButtonWidth(), model.getButtonHeight());
   } else {
      // Draw the button
      XDrawRectangle(xdat.display, xdat.window, xdat.gc, 
	    model.getButtonX(), model.getButtonY(),
	    model.getButtonWidth(), model.getButtonHeight());

      drawStartButtonText();
   }
}

// Write the word "Start"
void SplashDrawer::drawStartButtonText() {
   xdat.setFont("-*-helvetica-*-*-*-*-25-*-*-*-*-*-*-*");
   const char *label = "Start";
   
   int string_height = xdat.currentFontHeight();
   int string_width = xdat.renderedWidthOfString(label);
   int xloc = model.getButtonX() + (model.getButtonWidth() - string_width) / 2;
   int yloc = model.getButtonY() + string_height + 7;
   
   xdat.drawString(label, xloc, yloc);
}
