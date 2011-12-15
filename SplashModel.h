// StartModel.h

#ifndef __SPLASH_MODEL_H__
#define __SPLASH_MODEL_H__

#include "ModelBase.h"

class SplashModel : public ModelBase {
   public:
      SplashModel();
      bool isButtonPressed();
      void setButtonPressed();
      void setButtonUnpressed();
      bool buttonIsActivated();
      void setButtonActivated();

      int getButtonX();
      int getButtonY();
      int getButtonWidth();
      int getButtonHeight();

   private:
      bool buttonPressed;
      bool buttonActivated;
};

#endif // __SPLASH_MODEL_H__
