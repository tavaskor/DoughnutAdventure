#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
   Display *display = XOpenDisplay("");
   XAutoRepeatOn(display);
   XCloseDisplay(display);

   return 0;
}
