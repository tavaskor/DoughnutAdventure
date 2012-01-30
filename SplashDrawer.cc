#include "SplashDrawer.h"
#include "WindowConstants.h"

#include <string>
using std::string;

SplashDrawer::SplashDrawer(XData &xdata, SplashModel &sm) :
        GraphicsDrawer(xdata), model(sm) {
   model.addView(*this);
}


void SplashDrawer::redraw() {
    xdat.clearWindow();
    drawHeadingInformation();
    drawImmediateInstructions();
    drawGameText();
    drawStartButton();
    xdat.flushDisplay();
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
	const static char* opening_lines[] = {
		"Game play instructions:",
		"Press j and k to move left and right.  Press spacebar to jump.",
		"Press 1 to set the difficulty to easy or 2 to set the difficulty to hard.",
		"Press p to pause, or q to quit at any time.",
		"The game ends when your weight drops below 100 pounds.",
		"Doughnuts increase your weight; all other foods decrease it."
	};
	
   xdat.setFont("-*-helvetica-*-r-*-*-12-*-*-*-*-*-*-*");

	const size_t NUM_STRINGS = sizeof(opening_lines) / sizeof(opening_lines[0]);

   for (size_t i = 0; i < NUM_STRINGS; i++) {
	   const char* label = opening_lines[i];
	   xdat.drawString(label, 130 + (20 * i), CENTRE);
   }
}


void SplashDrawer::drawStartButton() {
   xdat.drawRectangle(model.getButtonX(), model.getButtonY(),
        model.getButtonWidth(), model.getButtonHeight(), model.isButtonPressed());
   if (!model.isButtonPressed()) {
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
