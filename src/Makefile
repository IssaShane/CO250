CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -MMD
OUTDIR = ../out
EXEC = Simplex
OBJECTS = linear_sys/linear_systems.o lib_vector/fraction.o lib_vector/matrix_tools.o lib_vector/vector_tools.o simplex/simplex.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
