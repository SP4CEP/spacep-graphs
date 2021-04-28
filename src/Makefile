digraph.out: main.cpp digraph.cpp linkedlist.cpp graph.cpp network.cpp
	g++ main.cpp digraph.cpp linkedlist.cpp graph.cpp network.cpp -o digraph.out
network.out: main.cpp network.cpp linkedlist.cpp
	g++ main.cpp network.cpp linkedlist.cpp -o network.out
graph.out: main_graph.cpp graph.cpp linkedlist.cpp
	g++ main.cpp graph.cpp linkedlist.cpp -o graph.out
list.out: main.cpp linkedlist.cpp
	g++ main_lista.cpp linkedlist.cpp -o list.out
clean:
	rm *.out
