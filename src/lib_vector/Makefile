CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -MMD
OUTDIR = ../out
EXEC = LibVec
OBJECTS = fraction.o matrix_tools.o vector_tools.o test_libvec.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
