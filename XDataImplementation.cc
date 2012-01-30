#include "XDataImplementation.h"

#include "WindowConstants.h"

#include <iostream>

XDataImplementation::XDataImplementation(int border_width) {
	// Open the display first
	display = XOpenDisplay("");
	if ( !display ) {
		std::cerr << "Unable to open the display." << std::endl;
		exit(0);
	}
	
	// Get the default screen
	int screen = DefaultScreen(display);
	
	// Get the background and foreground colours
	unsigned long background = BlackPixel(display, screen);
	unsigned long foreground = WhitePixel(display, screen);
	
	// Set up size and location of window
	XSizeHints hints;
	int displayWidth = DisplayWidth(display, screen);
	int displayHeight = DisplayHeight(display, screen);
	
	hints.width = WINDOW_WIDTH;
	hints.height = WINDOW_HEIGHT;
	hints.x = displayWidth / 2 - WINDOW_WIDTH / 2;
	hints.y = displayHeight / 2 - WINDOW_HEIGHT / 2;
	hints.flags = PPosition | PSize;
	
	// Create a simple window, and set the basic properties of it
	window = XCreateSimpleWindow(display,
									   DefaultRootWindow( display ), hints.x, hints.y,
									   hints.width, hints.height, border_width, foreground, background );
	XSetStandardProperties( display, window, 
						   "Doughnut Adventure", "Doughnut Adventure",
						   None, NULL, 0, &hints );
	
	// Next, create a graphics context and set the colours that are going
	// to be used for drawing
	gc = XCreateGC (display, window, 0, 0 );
	XSetBackground(display, gc, background);
	XSetForeground(display, gc, foreground);
}

XDataImplementation::~XDataImplementation() {
	// Unload all of the fonts that were loaded.  Hopefully there weren't many,
	// and this hasn't represented too much wasted space...
	
	while (!fontCache.empty()) {
		XFontStruct *nextFont = fontCache.begin()->second;
		XFreeFont(display, nextFont);
		fontCache.erase(fontCache.begin());
	}
}


void XDataImplementation::setFont(const char *font_name) {
	std::map<const char*, XFontStruct*>::iterator font_iter = fontCache.find(font_name);
	if (font_iter == fontCache.end()) {
		currentFont = XLoadQueryFont(display, font_name);
		fontCache[font_name] = currentFont;
	} else {
		currentFont = font_iter->second;
	}

	XSetFont(display, gc, currentFont->fid);
}
