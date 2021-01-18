#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "linkedlist.h"
#include "graphstructs.h"

using std::string;

class Graph {
    LinkedList<GraphNode> nodes;

public:
    Graph();

    ~Graph();

    bool add_node(string tag);
    bool add_edge(string node1_tag, string node2_tag, string edge_tag);

    bool remove_node(string tag);
    bool remove_edge(string node1_tag, string node2_tag);
    bool remove_edge(string tag);

    bool find_node(string tag);
    bool find_edge(string node1_tag, string node2_tag);
    bool find_edge(string tag);

    GraphNode* get_node(string tag);

    int node_degree(string tag);

    int node_count();
    int edge_count();

    bool remove_edges(string tag);

    void clear();

    void print();

};

#endif // GRAPH_H_INCLUDED
