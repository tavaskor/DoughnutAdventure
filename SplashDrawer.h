// StartDrawer.h
#ifndef __SPLASH_DRAWER_H__
#define __SPLASH_DRAWER_H__

#include "GraphicsDrawer.h"
#include "StartModel.h"

class SplashDrawer : public GraphicsDrawer {
   public:
      SplashDrawer(XData &xdata, StartModel &sm);
      virtual void redraw();

   protected:
      virtual const char* getHeader() = 0;
      virtual const char* getInstruction() = 0;

   private:
      StartModel &model;

      void drawHeadingInformation();
      void drawImmediateInstructions();
      void drawGameText();
      void drawStartButton();
      void drawStartButtonText();
};

#endif // __SPLASH_DRAWER_H__
