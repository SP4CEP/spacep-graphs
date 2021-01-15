#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <stdlib>

#include "linkedlist.h"

struct GraphNode {
    // etiqueta
    LinkedList<GraphNode*> in_edges, out_edges;
};

class Graph{
public:
    LinkedList<GraphNode> nodes;


    Graph();

    ~Graph();

    bool add_node(/*etiqueta*/);
    bool add_edge(/*etiquetanodo1, etiquetanodo2, peso?, etiqueta?*/);

    bool remove_node(/*etiqueta nodo*/);
    bool remove_edge(/*etiquetanodo1?, etiquetanodo2?, etiqueta?*/);

    bool find_node(/*etiqueta*/);
    bool find_edge(/*etiquetanodo1?, etiquetanodo2?, etiqueta?*/);

    int node_degree(/*etiqueta*/);

    int node_count();
    int edge_count();

    bool remove_edges(/*etiqueta nodo*/);

    void clear();

    void print();

};

#endif // GRAPH_H_INCLUDED
