// GraphicsDrawer.h
#ifndef __GRAPHICS_DRAWER_H__
#define __GRAPHICS_DRAWER_H__

#include "XData.h"

class GraphicsDrawer {
   public:
      GraphicsDrawer(XData &xdata);
      virtual ~GraphicsDrawer() {}
      virtual void redraw() = 0;

   protected:
      XData &xdat;
};

#endif // __GRAPHICS_DRAWER_H__
