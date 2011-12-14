#include "ModelBase.h"

#include <vector>
using std::vector;

ModelBase::~ModelBase() {}

void ModelBase::addView(GraphicsDrawer &gd) {
   viewables.push_back(&gd);
}

void ModelBase::updateAllViews() {
   for (vector<GraphicsDrawer*>::iterator iter = viewables.begin();
	 iter != viewables.end(); iter++) {
      (*iter)->redraw();
   }
}
