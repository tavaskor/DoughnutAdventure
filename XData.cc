#include "XData.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>

#include "WindowConstants.h"
#include "EasyFoodGenerator.h"

struct XDataImplementation {
   Display *display;
   Window window;
   GC gc;

   XFontStruct *currentFont;
   XEvent currentEvent;
};

XData::XData(int argc, char **argv, int border_width) : 
        impl(new XDataImplementation()) {
   // Open the display first
   impl->display = XOpenDisplay("");
   if ( !impl->display ) {
      std::cerr << "Unable to open the display." << std::endl;
      exit(0);
   }

   // Get the default screen
   int screen = DefaultScreen(impl->display);

   // Get the background and foreground colours
   unsigned long background = BlackPixel(impl->display, screen);
   unsigned long foreground = WhitePixel(impl->display, screen);

   // Set up size and location of window
   XSizeHints hints;
   int displayWidth = DisplayWidth(impl->display, screen);
   int displayHeight = DisplayHeight(impl->display, screen);

   hints.width = WINDOW_WIDTH;
   hints.height = WINDOW_HEIGHT;
   hints.x = displayWidth / 2 - WINDOW_WIDTH / 2;
   hints.y = displayHeight / 2 - WINDOW_HEIGHT / 2;
   hints.flags = PPosition | PSize;

   // Create a simple window, and set the basic properties of it
   impl->window = XCreateSimpleWindow(impl->display,
	 DefaultRootWindow( impl->display ), hints.x, hints.y,
	 hints.width, hints.height, border_width, foreground, background );
   XSetStandardProperties( impl->display, impl->window, 
	 "Doughnut Adventure", "Doughnut Adventure",
	 None, NULL, 0, &hints );

   // Next, create a graphics context and set the colours that are going
   // to be used for drawing
   impl->gc = XCreateGC (impl->display, impl->window, 0, 0 );
   XSetBackground(impl->display, impl->gc, background);
   XSetForeground(impl->display, impl->gc, foreground);

   XMapRaised(impl->display, impl->window);
   XFlush(impl->display);  // Doesn't display without this

   // Excessive, but handle all events that may need handling, regardless
   // of whether it will be relevant in the current context.
   XSelectInput( impl->display, impl->window, 
         ExposureMask | KeyPressMask | KeyReleaseMask | 
         ButtonPressMask | ButtonReleaseMask | ButtonMotionMask );
   
   // Prepare for starting the game.
   XAutoRepeatOff(impl->display);
}

XData::~XData() {
   delete impl;
}

void XData::setFont(const char *font_name) {
   impl->currentFont = XLoadQueryFont(impl->display, font_name);
   XSetFont(impl->display, impl->gc, impl->currentFont->fid);
}

int XData::currentFontHeight() {
    return impl->currentFont->ascent + impl->currentFont->descent;
}

int XData::renderedWidthOfString(const char* str) {
    return XTextWidth(impl->currentFont, str, strlen(str));
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
    XDrawString(impl->display, impl->window, impl->gc, 
            xDisplacement, yDisplacement,
            str, strlen(str));
}

void XData::drawRectangle(int x, int y, unsigned int width, unsigned int height, bool fill) {
    int (*toCall)(Display*, Drawable, GC, int, int, unsigned int, unsigned int);
    toCall = fill ? &XFillRectangle : &XDrawRectangle;
    (*toCall)(impl->display, impl->window, impl->gc, x, y, width, height);
}

void XData::drawArc(int x, int y, unsigned int width, unsigned int height,
                int angle1, int angle2, bool fill) {
    int (*toCall)(Display*, Drawable, GC, int, int, unsigned int, unsigned int, int, int);
    toCall = fill ? &XFillArc : &XDrawArc;
    (*toCall)(impl->display, impl->window, impl->gc, x, y, width, height, angle1, angle2);
}

void XData::drawLine(int x1, int y1, int x2, int y2) {
    XDrawLine(impl->display, impl->window, impl->gc, x1, y1, x2, y2);
}

void XData::clearWindow() {
   XClearWindow(impl->display, impl->window);
}

void XData::flushDisplay() {
   XFlush(impl->display);
}

int XData::eventPending() {
   if ( XPending(impl->display)) {
      XNextEvent(impl->display, &(impl->currentEvent));
      return impl->currentEvent.type;
   }
   return false;
}

char XData::getPressedKey() const {
   const static int BUFFER_SIZE = 10;
   const static int BAD_RETURN = '\0';

   static char text[BUFFER_SIZE];
   KeySym key;
   int i;

   if (impl->currentEvent.type == KeyPress || impl->currentEvent.type == KeyRelease) {
      i = XLookupString( (XKeyEvent *) &impl->currentEvent, text, BUFFER_SIZE, &key, 0);
      if (i == 1) {
         return tolower(text[0]);
      }
   }
   return BAD_RETURN;
}

int XData::getMouseX() const {
   return impl->currentEvent.xbutton.x;
}

int XData::getMouseY() const {
   return impl->currentEvent.xbutton.y;
}

void XData::finalCleanup() {
    XAutoRepeatOn(impl->display);
    XCloseDisplay(impl->display);
}
