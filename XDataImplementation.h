#ifndef __XDATA_IMPLEMENTATION_H__
#define __XDATA_IMPLEMENTATION_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <map>

struct XDataImplementation {
	Display *display;
	Window window;
	GC gc;
	
	XFontStruct *currentFont;
	XEvent currentEvent;
	
	XDataImplementation(int border_width);
	~XDataImplementation();
	void setFont(const char *font_name);
	
private:
	std::map<const char*, XFontStruct*> fontCache;
};

#endif //__XDATA_IMPLEMENTATION_H__