#ifndef DIGRAPH_H_INCLUDED
#define DIGRAPH_H_INCLUDED

#include "linkedlist.h"
#include "graphstructs.h"
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
class Digraph {
    int num_edges;
    int num_nodes;
    int weighted;
    float weight;
    LinkedList<DigraphNode> nodes;

public:

    /**
    * @brief Constructor for Graph
    **/
    Digraph();

    /**
    * @brief Copy constructor for Graph
    **/
    Digraph(const Digraph&);

    /**
    * @brief Destructor for Graph
    **/
    ~Digraph();

    /**
     * 
     */
    void set_type(int t);
    
    /**
     * 
     */
    float get_weight();

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
    bool add_edge(string node1_tag, string node2_tag, string edge_tag, float weight=0);

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
    DigraphNode* get_node(string tag);

    /**
     * @brief Function that obtains node's degree of input of given node
     * @param tag node's tag
     **/
    int in_node_degree(string tag);

    /**
     * @brief Function that obtains node's degree of output of given node
     * @param tag node's tag
     **/
    int out_node_degree(string tag);
    /**
     * @brief Function that obtains node's degree of given node
     * @param tag node's tag
     **/
    int node_degree(DigraphNode node);

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

    /**
    * @brief Overload for = operator
    **/
    Digraph& operator=(const Digraph &);

    Digraph dijkstra(string initial_tag, string destination_tag="");

};

#endif // DIGRAPH_H_INCLUDED