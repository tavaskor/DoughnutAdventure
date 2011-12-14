// StartModel.h

#ifndef __START_MODEL_H__
#define __START_MODEL_H__

#include "ModelBase.h"

class StartModel : public ModelBase {
   public:
      StartModel();
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

#endif // __START_MODEL_H__
