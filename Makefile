all: myLSCC

myLSCC: myLSCC.cpp graph.h localSearch.h constants.h \
					myBijection.h operandSets.h vertexLinkedQueue.h cliqueHash.h \
					longDoubleComparison.h
	g++ -std=gnu++0x -O3 -static myLSCC.cpp -o myLSCC

clean: rm -f *~
