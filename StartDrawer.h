// StartDrawer.h
#ifndef __START_DRAWER_H__
#define __START_DRAWER_H__

#include "SplashDrawer.h"
#include "StartModel.h"

class StartDrawer : public SplashDrawer {
   public:
      StartDrawer(XData &xdata, StartModel &sm);

   protected:
      virtual const char* getHeader();
      virtual const char* getInstruction();
};

#endif // __START_DRAWER_H__
