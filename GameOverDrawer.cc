#include "GameOverDrawer.h"

GameOverDrawer::GameOverDrawer(XData &xdata,
            SplashModel &sm) : SplashDrawer(xdata, sm) {
      this->redraw();
}

const char* GameOverDrawer::getHeader() {
      return "Game Over";
}

const char* GameOverDrawer::getInstruction() {
      return "Press Q to quit, or click Start to play again.";
}
