#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "linkedlist.h"
#include "graphstructs.h"
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
class Graph {
    int num_edges;
    int num_nodes;
    int weighted;
    float weight;
    LinkedList<GraphNode> nodes;

public:

    /**
    * @brief Constructor for Graph
    **/
    Graph();

    /**
    * @brief Copy constructor for Graph
    **/
    Graph(const Graph&);

    /**
    * @brief Destructor for Graph
    **/
    ~Graph();

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
    GraphNode* get_node(string tag);

    /**
     * @brief Function that obtains node's degree of given node
     * @param tag node's tag
     **/
    int node_degree(string tag);

    /**
     * @brief Function that obtains node's degree of given node
     * @param tag node's tag
     **/
    int node_degree(GraphNode node);

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
    Graph& operator=(const Graph &);

    /**
    * @brief Function that determines if graph is bipartite
    **/
    bool is_bipartite(LinkedList<string> *P1=nullptr, LinkedList<string> *P2=nullptr);

    /**
    * @brief Function that returns an eulerian path
    **/
    bool find_eulerian_path(vector<string> *P1=nullptr);

    /**
    * @brief Function that performs a breadth first search and returns the
    * found forest of spanning trees
    **/
    vector<Graph> bfs();

    /**
    * @brief Function that performs a depth first search and returns the
    * found forest of spanning trees
    **/
    vector<Graph> dfs();

    /**
     * @brief Finds the root of a node given its tag on the Union-Find Set
     * @param node Node to find its root
     * @param param Map of nodes' parents
     * @return The tag of the parent
     **/
    string find_root(string node, unordered_map<string, string> &parent);

    /**
     * @brief Makes node2 the parent of node1 on the Union-Find Set
     * @param node1 Node to set as child of the other
     * @param node2 Node to set as parent of the other
     * @param param Map of nodes' parents
     * @return The tag of the parent
     **/
    void union_root(string node1, string node2, unordered_map<string, string> &parent);

    /**
     * @brief Function that performs the kruskal algorithm and returns the
     * found forest of spanning trees
     * @param expansion_tree A Graph to store the minimum-expansion tree.
     * @return True if the graph is connected, false otherwise
     **/
    bool kruskal(Graph &expansion_tree);

    /**
     * @brief Function that performs the primm algorithm and returns the
     * found forest of spanning trees
     * @param expansion_tree A Graph to store the minimum-expansion tree.
     * @return True if the graph is connected, false otherwise
     **/
    bool prim(vector<Graph> &expansion_tree_forest);
};

#endif // GRAPH_H_INCLUDED
