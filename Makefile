CXX=g++
CXXFLAGS= -std=c++11 #-Wall -g
# Uncomment for parser DEBUG
#DEFS=-DDEBUG


all: bst-test equal-paths-test

bst-test: bst-test.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@
	./bst-test

# Brute force recompile all files each time
equal-paths-test: equal-paths-test.cpp equal-paths.cpp equal-paths.h
	$(CXX) $(CXXFLAGS) $(DEFS) equal-paths-test.cpp equal-paths.cpp -o $@
	#./equal-paths-test

clean:
	rm -f *~ *.o bst-test equal-paths-test

