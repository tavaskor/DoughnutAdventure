// ModelBase.h

#ifndef __MODEL_BASE_H__
#define __MODEL_BASE_H__

#include <vector>

#include "GraphicsDrawer.h"

class ModelBase {
   public:
      virtual ~ModelBase();
      virtual void addView(GraphicsDrawer &gd);

   protected:
      virtual void updateAllViews();

   private:
      std::vector<GraphicsDrawer*> viewables;
};

#endif // __MODEL_BASE_H__
