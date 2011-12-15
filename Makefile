CXX=g++
CXXFLAGS=-g -Wall -ansi -pedantic
LDFLAGS=-L/usr/X11R6/lib -lX11

ALL_EXE=${A1EXE} ${AFTEREXE}
A1EXE=doughnut_adventure
AFTEREXE=after_doughnut_adventure

ALL_OBJS=${A1MAINOBJS} ${AFTEROBJS}
ALL_SRC=${ALL_OBJS:.o=.cc}
ALL_DEPS=${ALL_OBJS:.o=.d}

A1MAINOBJS=main.o XData.o ${EVENTOBJS} ${DRAWOBJS} ${MODELOBJS}
EVENTOBJS=EventHandler.o StartHandler.o GameHandler.o
DRAWOBJS=GraphicsDrawer.o SplashDrawer.o GameDrawer.o \
	 StartDrawer.o GameOverDrawer.o
MODELOBJS=ModelBase.o StartModel.o GameModel.o ${GAMEPARTS} 
GAMEPARTS=Object.o Player.o Food.o FoodGenerator.o \
	  EasyFoodGenerator.o HardFoodGenerator.o
AFTEROBJS=onexit.o

.phony: ALL
ALL: ${A1EXE} ${AFTEREXE}

${A1EXE}: ${A1MAINOBJS}
	${CXX} -o ${A1EXE} ${A1MAINOBJS} ${LDFLAGS}

${AFTEREXE}: ${AFTEROBJS}
	${CXX} -o ${AFTEREXE} ${AFTEROBJS} ${LDFLAGS}

%.d: %.cc
	${CXX} -MM $< > $@

include ${ALL_DEPS}

clean:
	rm -f ${ALL_EXE} ${ALL_OBJS} ${ALL_DEPS}
