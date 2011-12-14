#include "XData.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
using std::cerr;
using std::endl;

#include "WindowConstants.h"


XData::XData(int argc, char **argv, int border_width) {
   // Open the display first
   this->display = XOpenDisplay("");
   if ( !this->display ) {
      cerr << "Unable to open the display." << endl;
      exit(0);
   }

   // Get the default screen
   this->screen = DefaultScreen(this->display);

   // Get the background and foreground colours
   unsigned long background = BlackPixel(this->display, this->screen);
   unsigned long foreground = WhitePixel(this->display, this->screen);

   // Set up size and location of window
   XSizeHints hints;
   int displayWidth = DisplayWidth(this->display, this->screen);
   int displayHeight = DisplayHeight(this->display, this->screen);

   hints.width = WINDOW_WIDTH;
   hints.height = WINDOW_HEIGHT;
   hints.x = displayWidth / 2 - WINDOW_WIDTH / 2;
   hints.y = displayHeight / 2 - WINDOW_HEIGHT / 2;
   hints.flags = PPosition | PSize;

   // Create a simple window, and set the basic properties of it
   this->window = XCreateSimpleWindow(this->display,
	 DefaultRootWindow( this->display ), hints.x, hints.y,
	 hints.width, hints.height, BORDER_WIDTH, foreground, background );
   XSetStandardProperties( this->display, this->window, 
	 "Doughnut Adventure", "Doughnut Adventure",
	 None, NULL, 0, &hints );

   // Next, create a graphics context and set the colours that are going
   // to be used for drawing
   this->gc = XCreateGC (this->display, this->window, 0, 0 );
   XSetBackground(this->display, this->gc, background);
   XSetForeground(this->display, this->gc, foreground);

   XMapRaised(this->display, this->window);
   XFlush(this->display);  // Doesn't display without this
}

// Tell the window manager which inputs are needed
void XData::selectInput(long event_mask) {
   XSelectInput( this->display, this->window, event_mask);
}
