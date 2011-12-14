#include "StartModel.h"

#include "WindowConstants.h"

StartModel::StartModel() : buttonPressed(false), buttonActivated(false) {}

bool StartModel::isButtonPressed() { return buttonPressed; }
void StartModel::setButtonPressed() { buttonPressed = true; updateAllViews(); }
void StartModel::setButtonUnpressed() { buttonPressed = false; updateAllViews(); }
bool StartModel::buttonIsActivated() { return buttonActivated; }
void StartModel::setButtonActivated() { buttonActivated = true; }

int StartModel::getButtonX() {
   return ( WINDOW_WIDTH/2 - getButtonWidth()/2 );
}

int StartModel::getButtonY() {
   return ( WINDOW_HEIGHT - getButtonHeight() - 10 );
}

int StartModel::getButtonWidth() {
   return 100;
}

int StartModel::getButtonHeight() {
   return 50;
}
