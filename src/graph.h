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

    /**
     * @brief Function that obtains node's degree of given node
     * @param tag node's tag 
     **/
    int node_degree(string tag);

    /**
     *@brief Function that obtains graph's node count
     **/
    int node_count();

    /**
     *@brief Function that obtains graph's edge count
     **/
    int edge_count();

    /**
     *@brief Function that removes all incising edges of given a node
     *@param tag node's tag which edges will be removed
     **/
    bool remove_edges(string tag);

    /**
     *@brief Function to clear all graph's nodes and edges
     **/
    void clear();

    /**
     *@brief Function to print the graph
     **/
    void print();

};

#endif // GRAPH_H_INCLUDED
