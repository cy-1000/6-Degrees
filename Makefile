# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder actorconnections extension



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o ActorEdge.o ActorNode.o Movie.o UnionFind.o pathfinder.cpp

test: ActorGraph.o ActorEdge.o ActorNode.o Movie.o UnionFind.o test.cpp

actorconnections: ActorGraph.o ActorEdge.o ActorNode.o Movie.o UnionFind.o actorconnections.cpp

extension:  TwitterGraph.o TwitterNode.o extension.cpp

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

actorconnections: ActorGraph.o

ActorGraph.o: ActorGraph.h UnionFind.h Movie.o ActorNode.o ActorEdge.o UnionFind.o

ActorNode.o: ActorNode.h ActorEdge.h

UnionFind.o: UnionFind.h

ActorEdge.o: ActorNode.h ActorEdge.h

Movie.o: Movie.h

TwitterNode.o: TwitterNode.h

TwitterGraph.o: TwitterGraph.h TwitterNode.o


clean:
	rm -f pathfinder actorconnections stronglyconnected *.o core*

