CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = biquadris
OBJECTS = gameplay.o text.o block.o basicblock.o control.o level.o level0.o board.o level1.o level2.o level3.o level4.o window.o commander.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
