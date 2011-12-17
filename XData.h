#ifndef __XDATA_H__
#define __XDATA_H__

#include <X11/Xlib.h>
#include <X11/Xutil.h>

enum TextAlignment { LEFT, CENTRE, RIGHT };

// TODO:
// Make the data private,
// and replace the following cases?
// * gc in GameDrawer, SplashDrawer
// * window in EventHandler, GameDrawer, SplashDrawer
// * display in EventHandler, GameDrawer, GameHandler, SplashDrawer, SplashHandler, onexit (!)
class XData {
   public:
      XData(int argc = 0, char **argv = NULL, int border_width = BORDER_WIDTH);
      void selectInput(long event_mask);
      
      void setFont(const char *fontName);
      int currentFontHeight();
      int renderedWidthOfString(const char *str);
      void drawString(const char *str, int yDisplacement, TextAlignment align);
      void drawString(const char *str, int xDisplacement, int yDisplacement);
      
      void drawRectangle(int x, int y, unsigned int width, unsigned int height, bool fill = false);
      void drawArc(int x, int y, unsigned int width, unsigned int height,
                int angle1, int angle2, bool fill = false);
      void drawLine(int x1, int y1, int x2, int y2);
      
      void clearWindow();
      void flushDisplay();
      
      bool pending();
      XEvent* getNextEvent();
      
      
      void finalCleanup();
      
      
   private:
       Display *display;
       Window window;
       GC gc;
       
       const static int BORDER_WIDTH = 5;
       
       XFontStruct *currentFont;
};

#endif // __XDATA_H__
