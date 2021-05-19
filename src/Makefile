testing.out: main_testing.cpp digraph.cpp linkedlist.cpp graph.cpp network.cpp
	g++ main_testing.cpp digraph.cpp linkedlist.cpp graph.cpp network.cpp -o testing.out
network.out: main.cpp network.cpp linkedlist.cpp
	g++ main.cpp network.cpp linkedlist.cpp -o network.out
digraph.out: main.cpp digraph.cpp linkedlist.cpp
	g++ main.cpp network.cpp linkedlist.cpp -o digraph.out
graph.out: main_graph.cpp graph.cpp linkedlist.cpp
	g++ main.cpp graph.cpp linkedlist.cpp -o graph.out
list.out: main.cpp linkedlist.cpp
	g++ main_lista.cpp linkedlist.cpp -o list.out
all.out: main.cpp digraph.cpp linkedlist.cpp graph.cpp network.cpp
	g++ main.cpp digraph.cpp linkedlist.cpp graph.cpp network.cpp -o all.out
clean:
	rm *.out
