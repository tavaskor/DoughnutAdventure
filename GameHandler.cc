#include "GameHandler.h"

#include <iostream>
using std::cerr;
using std::endl;

GameHandler::GameHandler(XData &xdata, GraphicsDrawer &graphdraw, 
      GameModel &gm) : EventHandler(xdata, graphdraw), model(gm) {
   this->selectInput( KeyPressMask | KeyReleaseMask );
   XAutoRepeatOff(xdata.display);
}

void GameHandler::handleOtherEvents(XEvent &event) {
   const int BUFFER_SIZE = 10;
   char text[BUFFER_SIZE];
   KeySym key;
   int i;

   switch(event.type) {
      case KeyPress:
	 i = XLookupString( (XKeyEvent *) &event, text, BUFFER_SIZE,
	       &key, 0);
	 if (i == 1) {
	    switch( text[0] ) {
	       case '1':
		  model.setDifficulty(EASY);
		  break;
	       case '2':
		  model.setDifficulty(HARD);
		  break;
	       case 'p':
	       case 'P':
		  model.setKeyPressed('p');
		  model.togglePaused();
	       case 'i':
	       case 'I':
		  model.setKeyPressed('i');
		  break;
	       case 'j':
	       case 'J':
		  model.setKeyPressed('j');
		  break;
	       case 'k':
	       case 'K':
		  model.setKeyPressed('k');
		  break;
	       case 'm':
	       case 'M':
		  model.setKeyPressed('m');
		  break;
	       case ' ':
		  model.setKeyPressed(' ');
		  break;
	    }
	 }
	 break;
      case KeyRelease:
	 i = XLookupString( (XKeyEvent *) &event, text, BUFFER_SIZE,
	       &key, 0);
	 if (i == 1) {
	    switch( text[0] ) {
	       case 'i':
	       case 'I':
		  model.setKeyUnpressed('i');
		  break;
	       case 'j':
	       case 'J':
		  model.setKeyUnpressed('j');
		  break;
	       case 'k':
	       case 'K':
		  model.setKeyUnpressed('k');
		  break;
	       case 'm':
	       case 'M':
		  model.setKeyUnpressed('m');
		  break;
	       case ' ':
		  model.setKeyUnpressed(' ');
		  break;
	    }
	 }
	 break;
   }
}
