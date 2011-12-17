// GameDrawer.cc

#include "GameDrawer.h"
#include "WindowConstants.h"
#include "GameModel.h"

#include <sstream>
#include <string>
using std::stringstream;
using std::string;

GameDrawer::GameDrawer(XData &xdata, GameModel &gm) : 
        GraphicsDrawer(xdata), model(gm), 
        player(gm.getPlayer()), foodList(gm.getFoodList()) {
   this->redraw();
   model.addView(*this);
}

void GameDrawer::redraw() {
   XClearWindow( xdat.display, xdat.window );
   drawPlayer();
   drawFood();
   drawConveyorBelt();
   drawStatusBar();
   if (model.gamePaused()) {
      drawPaused();
   }
   XFlush(xdat.display);
}

void GameDrawer::drawPlayer() {
   // Draw the head
   this->drawEllipse( player.getLeftX() + player.getWidth() / 2,
	 player.getBottomY() + player.getHeight() - 4, 8, 8);

   // Draw the body
   this->fillEllipse( player.getLeftX() + player.getWidth() / 2, 
	 (player.getHeight() / 2) + player.getBottomY() - 4,
	 player.getWidth(), (player.getHeight() - 8) );

   // Feet and hands
   this->drawLine( player.getLeftX(), player.getBottomY() + player.getHeight(),
	 player.getLeftX() + player.getWidth(), player.getBottomY());
   this->drawLine( player.getLeftX(), player.getBottomY(),
	 player.getLeftX() + player.getWidth(),
	 player.getBottomY() + player.getHeight() );
}

void GameDrawer::drawFood() {
   for (std::list<Food>::const_iterator iter = foodList.begin();
	 iter != foodList.end(); iter++) {
      switch ( iter->getFoodType() ) {
	 case DOUGHNUT:
	    this->drawDoughnut(*iter);
	    break;
	 case CHEESE:
	    this->drawCheese(*iter);
	    break;
	 case CELERY:
	    this->drawCelery(*iter);
	    break;
	 case CARROT:
	    this->drawCarrot(*iter);
	    break;
	 default:
	    this->drawRectangle( iter->getLeftX(), iter->getBottomY(),
		  iter->getWidth(), iter->getHeight() );
	    break;
      }
   }
}

void GameDrawer::drawDoughnut(const Object &doughnut) {
   int centreX = doughnut.getLeftX() + ( doughnut.getWidth() / 2 );
   int centreY = doughnut.getBottomY() + (doughnut.getHeight() / 2);
   this->drawEllipse( centreX, centreY, doughnut.getWidth(), 
	 doughnut.getHeight() );
   this->drawEllipse( centreX, centreY, doughnut.getWidth() / 2,
	 doughnut.getHeight() / 2 );
}

void GameDrawer::drawCheese(const Object &cheese) {
   this->drawLine( cheese.getLeftX(), cheese.getBottomY() + cheese.getHeight(),
	 cheese.getLeftX() + cheese.getWidth(),
	 cheese.getBottomY() + cheese.getHeight() );
   this->drawLine( cheese.getLeftX() + cheese.getWidth(),
	 cheese.getBottomY() + cheese.getHeight(),
	 cheese.getLeftX() + ( cheese.getWidth() / 2 ),
	 cheese.getBottomY() );
   this->drawLine( cheese.getLeftX() + ( cheese.getWidth() / 2 ),
	 cheese.getBottomY(),
	 cheese.getLeftX(), cheese.getBottomY() + cheese.getHeight() );
}

void GameDrawer::drawCelery(const Object &celery) {
   this->drawRectangle( celery.getLeftX(), celery.getBottomY(),
	 celery.getWidth(), celery.getHeight() );
   this->drawLine( celery.getLeftX(), 
	 celery.getBottomY() + ( celery.getHeight() / 4 ),
	 celery.getLeftX() + celery.getWidth(),
	 celery.getBottomY() + ( celery.getHeight() / 4 ) );
   this->drawLine( celery.getLeftX(),
	 celery.getBottomY() + ( celery.getHeight() * 3 / 4 ),
	 celery.getLeftX() + celery.getWidth(),
	 celery.getBottomY() + ( celery.getHeight() * 3 / 4 ) );
}

void GameDrawer::drawCarrot(const Object &carrot) {
   int topSideY = carrot.getBottomY() + ( carrot.getHeight() * 3 / 4 );
   int centreX = carrot.getLeftX() + ( carrot.getWidth() / 2 );

   this->drawLine( centreX, carrot.getHeight(), carrot.getLeftX(), topSideY );
   this->drawLine( carrot.getLeftX(), topSideY, centreX, carrot.getBottomY() );
   this->drawLine( centreX, carrot.getBottomY(),
	 carrot.getLeftX() + carrot.getWidth(), topSideY );
   this->drawLine( carrot.getLeftX() + carrot.getWidth(), topSideY,
	 centreX, carrot.getHeight() );
}

void GameDrawer::drawConveyorBelt() {
   this->fillRectangle( 0, 2, WINDOW_WIDTH, 3);
}


void GameDrawer::drawStatusBar() {
   const int STATUS_BAR_Y = WINDOW_HEIGHT - 8;
   xdat.setFont("-*-helvetica-*-*-*-*-10-*-*-*-*-*-*-*");

   // Display the weight in the bottom left
   stringstream ss;
   ss << player.getWeight();
   string weight;
   ss >> weight;

   string text = "Weight: " + weight;
   const char *toDisplay = text.c_str();
   xdat.drawString(toDisplay, STATUS_BAR_Y, LEFT);

   // Display the difficulty in the bottom right
   string diffic;
   GameDifficulty gd = model.getDifficulty();
   switch (gd) {
      case EASY:
	 diffic = "Easy";
	 break;
      case HARD:
	 diffic = "Hard";
	 break;
      default:
	 diffic = "Unknown";
	 break;
   }
   
   text = "Difficulty: " + diffic;
   toDisplay = text.c_str();
   xdat.renderedWidthOfString(toDisplay);
   xdat.drawString(toDisplay, STATUS_BAR_Y, RIGHT);
}

void GameDrawer::drawPaused() {
   xdat.setFont("-*-helvetica-*-r-*-*-34-*-*-*-*-*-*-*");

   const char *toDisplay = "PAUSED";
   xdat.drawString(toDisplay, WINDOW_HEIGHT / 2, CENTRE);
}

void GameDrawer::drawRectangle(int x, int y, int width, int height) {
    xdat.drawRectangle(x, WINDOW_HEIGHT - y - height - 20, width, height, false);
}

void GameDrawer::fillRectangle(int x, int y, int width, int height) {
    xdat.drawRectangle(x, WINDOW_HEIGHT - y - height - 20, width, height, true);
}

void GameDrawer::drawEllipse(int centreX, int centreY, int width, int height) {
    xdat.drawArc(centreX - (width/2), WINDOW_HEIGHT - centreY - (height/2) - 20,
            width, height, 0, 360*64, false);
}

void GameDrawer::fillEllipse(int centreX, int centreY, int width, int height) {
    xdat.drawArc(centreX - (width/2), WINDOW_HEIGHT - centreY - (height/2) - 20,
            width, height, 0, 360*64, true);
}

void GameDrawer::drawLine(int x1, int y1, int x2, int y2) {
    xdat.drawLine(x1, WINDOW_HEIGHT - y1 - 20, x2, WINDOW_HEIGHT - y2 - 20);
}
