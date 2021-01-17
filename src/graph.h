#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <stdlib>

#include "linkedlist.h"

struct GraphEdge {
    string tag;
    GraphNode* node;
};

struct GraphNode {
    string tag;
    LinkedList<GraphEdge> edges;
};

class Graph{
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

    int node_degree(/*etiqueta*/);

    int node_count();
    int edge_count();

    bool remove_edges(/*etiqueta nodo*/);

    void clear();

    void print();

};

#endif // GRAPH_H_INCLUDED
