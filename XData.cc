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
   int screen = DefaultScreen(this->display);

   // Get the background and foreground colours
   unsigned long background = BlackPixel(this->display, screen);
   unsigned long foreground = WhitePixel(this->display, screen);

   // Set up size and location of window
   XSizeHints hints;
   int displayWidth = DisplayWidth(this->display, screen);
   int displayHeight = DisplayHeight(this->display, screen);

   hints.width = WINDOW_WIDTH;
   hints.height = WINDOW_HEIGHT;
   hints.x = displayWidth / 2 - WINDOW_WIDTH / 2;
   hints.y = displayHeight / 2 - WINDOW_HEIGHT / 2;
   hints.flags = PPosition | PSize;

   // Create a simple window, and set the basic properties of it
   this->window = XCreateSimpleWindow(this->display,
	 DefaultRootWindow( this->display ), hints.x, hints.y,
	 hints.width, hints.height, border_width, foreground, background );
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

void XData::setFont(const char *font_name) {
   currentFont = XLoadQueryFont(this->display, font_name);
   XSetFont(this->display, this->gc, currentFont->fid);
}

int XData::currentFontHeight() {
    return currentFont->ascent + currentFont->descent;
}

int XData::renderedWidthOfString(const char* str) {
    return XTextWidth(currentFont, str, strlen(str));
}

void XData::drawString(const char *str, int yDisplacement, TextAlignment align) {
    const int window_buffer = 2;
    const int string_width = renderedWidthOfString(str);
    
    int xDisplacement;
    switch (align) {
        case CENTRE:
            xDisplacement = (WINDOW_WIDTH - string_width) / 2;
            break;
        case RIGHT:
            xDisplacement = WINDOW_WIDTH - string_width - window_buffer;
            break;
        default:
            xDisplacement = window_buffer;
            break;
    }
    
    drawString(str, xDisplacement, yDisplacement);
}

void XData::drawString(const char* str, int xDisplacement, int yDisplacement) {
    XDrawString(this->display, this->window, this->gc, 
            xDisplacement, yDisplacement,
            str, strlen(str));
}

void XData::drawRectangle(int x, int y, unsigned int width, unsigned int height, bool fill) {
    int (*toCall)(Display*, Drawable, GC, int, int, unsigned int, unsigned int);
    toCall = fill ? &XFillRectangle : &XDrawRectangle;
    (*toCall)(this->display, this->window, this->gc, x, y, width, height);
}

void XData::drawArc(int x, int y, unsigned int width, unsigned int height,
                int angle1, int angle2, bool fill) {
    int (*toCall)(Display*, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
    toCall = fill ? &XFillArc : &XDrawArc;
    (*toCall)(this->display, this->window, this->gc, x, y, width, height, angle1, angle2);
}

void XData::drawLine(int x1, int y1, int x2, int y2) {
    XDrawLine(this->display, this->window, this->gc, x1, y1, x2, y2);
}