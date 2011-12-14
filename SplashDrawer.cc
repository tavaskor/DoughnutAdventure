#include "SplashDrawer.h"
#include "WindowConstants.h"

#include <string>
using std::string;

SplashDrawer::SplashDrawer(XData &xdata, 
      StartModel &sm) : GraphicsDrawer(xdata), model(sm) {
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
   const char *font_name = "-*-helvetica-*-o-*-*-34-*-*-*-*-*-*-*";
   XFontStruct *font_info = XLoadQueryFont(xdat.display, font_name);
   XSetFont(xdat.display, xdat.gc, font_info->fid);

   const char *title = this->getHeader();
   int string_width = XTextWidth(font_info, title, strlen(title));
   int xloc = (WINDOW_WIDTH - string_width) / 2;
   int yloc = 50;
   XDrawString(xdat.display, xdat.window, xdat.gc, xloc, yloc,
	 title, strlen(title));
}

void SplashDrawer::drawImmediateInstructions() {
   const char *font_name = "-*-helvetica-*-r-*-*-17-*-*-*-*-*-*-*";
   XFontStruct *font_info = XLoadQueryFont(xdat.display, font_name);
   XSetFont(xdat.display, xdat.gc, font_info->fid);

   const char *title = this->getInstruction();
   int string_width = XTextWidth(font_info, title, strlen(title));
   int xloc = (WINDOW_WIDTH - string_width) / 2;
   int yloc = 90;
   XDrawString(xdat.display, xdat.window, xdat.gc, xloc, yloc,
	 title, strlen(title));
}


void SplashDrawer::drawGameText() {
   const char *font_name = "-*-helvetica-*-r-*-*-12-*-*-*-*-*-*-*";
   XFontStruct *font_info = XLoadQueryFont(xdat.display, font_name);
   XSetFont(xdat.display, xdat.gc, font_info->fid);

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

      int string_width = XTextWidth(font_info, label, strlen(label));
      int xloc = (WINDOW_WIDTH - string_width) / 2;
      int yloc = 130 + 20 * i;

      XDrawString(xdat.display, xdat.window, xdat.gc, xloc, yloc,
	    label, strlen(label));
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

void SplashDrawer::drawStartButtonText() {
   // Write the word "Start"
   const char *font_name = "-*-helvetica-*-*-*-*-25-*-*-*-*-*-*-*";
   const char *label = "Start";
   XFontStruct *font_info = XLoadQueryFont(xdat.display, font_name);
   XSetFont(xdat.display, xdat.gc, font_info->fid);

   int string_height = font_info->ascent + font_info->descent;
   int string_width = XTextWidth(font_info, label, strlen(label));
   int xloc = model.getButtonX() + (model.getButtonWidth() - string_width) / 2;
   int yloc = model.getButtonY() + string_height + 7;
   XDrawString(xdat.display, xdat.window, xdat.gc, xloc, yloc,
	 label, strlen(label));
}
