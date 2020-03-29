CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -MMD
EXEC = Linear
OBJECTS = test_linear_systems.o linear_systems.o fraction.o matrix_tools.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
