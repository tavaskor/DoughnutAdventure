#include "StartDrawer.h"


StartDrawer::StartDrawer(XData &xdata, 
      StartModel &sm) : SplashDrawer(xdata, sm) {
   this->redraw();
}

const char* StartDrawer::getHeader() {
   return "Doughnut Adventure";
}

const char* StartDrawer::getInstruction() {
   return "Click start to begin playing the game.";
}
