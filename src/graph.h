#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "linkedlist.h"
#include "graphstructs.h"

using std::string;

class Graph {
    LinkedList<GraphNode> nodes;

public:

    /**
    * @brief Constructor for Graph
    **/
    Graph();

    /**
    * @brief Destructor for Graph
    **/
    ~Graph();

    /**
     * @brief Function that adds a node.
     * @param tag Name for the node.
     * @return Whether the node was inserted.
     **/
    bool add_node(string tag);

    /**
    * @brief Function that adds an edge.
    * @param node1_tag Name for the first node.
    * @param node2_tag Name for the first node.
    * @param edge_tag Name for the edge.
    * @return Whether the edge was inserted.
    **/
    bool add_edge(string node1_tag, string node2_tag, string edge_tag);

    /**
    * @brief Function that removes a node.
    * @param tag Name of the node.
    * @return Whether the node was removed.
    **/
    bool remove_node(string tag);

    /**
    * @brief Function that removes an edge.
    * @param node1_tag Name of the node.
    * @param node2_tag Name of the node.
    * @return Whether the edge was removed.
    **/
    bool remove_edge(string node1_tag, string node2_tag);

    /**
    * @brief Function that removes an edge.
    * @param tag Name of the edge.
    * @return Whether the edge was removed.
    **/
    bool remove_edge(string tag);

    /**
    * @brief Finds a node.
    * @param tag Name of the node.
    * @return Whether the node was found.
    **/
    bool find_node(string tag);

    /**
    * @brief Finds a edge.
    * @param node1_tag Name of the first node.
    * @param node2_tag Name of the second node.
    * @return Whether the edge was found.
    **/
    bool find_edge(string node1_tag, string node2_tag);

    /**
    * @brief Finds a edge.
    * @param tag Name of the edge.
    * @return Whether the edge was found.
    **/
    bool find_edge(string tag);

    /**
    * @brief Gets a specific node.
    * @param tag Name of the node.
    * @return A pointer to the node.
    **/
    GraphNode* get_node(string tag);

    int node_degree(/*etiqueta*/);

    int node_count();
    int edge_count();

    bool remove_edges(/*etiqueta nodo*/);

    void clear();

    void print();

};

#endif // GRAPH_H_INCLUDED
