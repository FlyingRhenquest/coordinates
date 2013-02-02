CPPUNIT_CONTRIB=../../cppunit_contrib
TIME_LIB=../../time
OBJS = run_tests.o converter_test.o
EXE = run_tests
CFLAGS += -g --std=c++11 -I.. -I${CPPUNIT_CONTRIB} -I${TIME_LIB}
LFLAGS = -lcppunit

.cpp.o:
	g++ -c ${CFLAGS} $<

all: ${OBJS}
	g++ -o ${EXE} ${OBJS} ${LFLAGS}

clean:
	rm -f *~ ${EXE} ${OBJS} core
