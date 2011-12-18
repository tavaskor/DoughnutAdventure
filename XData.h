#ifndef __XDATA_H__
#define __XDATA_H__

// Desired forward declare to hide X11 details
struct XDataImplementation;

enum TextAlignment { LEFT, CENTRE, RIGHT };

class XData {
   public:
      XData(int argc = 0, char **argv = 0, int border_width = BORDER_WIDTH);
      ~XData();

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
      
      int eventPending();

      char getPressedKey() const;
      int getMouseX() const;
      int getMouseY() const;
      
      void finalCleanup();
      
   private:
      XDataImplementation *impl;

      const static int BORDER_WIDTH = 5;
};

#endif // __XDATA_H__
