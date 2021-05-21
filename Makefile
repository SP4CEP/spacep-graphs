CPATH=app/algorithms/src/
IPATH=app/algorithms/include/
BINPATH=bin/

all.out: $(CPATH)main.cpp $(CPATH)digraph.cpp $(CPATH)linkedlist.cpp $(CPATH)graph.cpp $(CPATH)network.cpp
	g++ -o $(BINPATH)all.out $(CPATH)main.cpp $(CPATH)digraph.cpp $(CPATH)linkedlist.cpp $(CPATH)graph.cpp $(CPATH)network.cpp -I$(IPATH).
clean:
	rm $(BINPATH)*.out

