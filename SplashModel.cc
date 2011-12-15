#include "SplashModel.h"

#include "WindowConstants.h"

SplashModel::SplashModel() : buttonPressed(false), buttonActivated(false) {}

bool SplashModel::isButtonPressed() { return buttonPressed; }
void SplashModel::setButtonPressed() { buttonPressed = true; updateAllViews(); }
void SplashModel::setButtonUnpressed() { buttonPressed = false; updateAllViews(); }
bool SplashModel::buttonIsActivated() { return buttonActivated; }
void SplashModel::setButtonActivated() { buttonActivated = true; }

int SplashModel::getButtonX() {
   return ( WINDOW_WIDTH/2 - getButtonWidth()/2 );
}

int SplashModel::getButtonY() {
   return ( WINDOW_HEIGHT - getButtonHeight() - 10 );
}

int SplashModel::getButtonWidth() {
   return 100;
}

int SplashModel::getButtonHeight() {
   return 50;
}
