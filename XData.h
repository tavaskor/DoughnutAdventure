#ifndef __XDATA_H__
#define __XDATA_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>

class XData {
   public:
      Display *display;
      int screen;
      Window window;
      GC gc;

      const static int BORDER_WIDTH = 5;

      XData(int argc = 0, char **argv = NULL, int border_width = BORDER_WIDTH);
      void selectInput(long event_mask);
};

#endif // __XDATA_H__
