#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED

#include <limits>
#include <vector>
#include <unordered_map>

#include "linkedlist.h"
#include "graphstructs.h"
#include "digraph.h"

using std::numeric_limits;
using std::vector;
using std::unordered_map;
using std::string;

class Network {
    int num_edges;
    int num_nodes;

    LinkedList<NetworkNode> nodes;

    vector<string> sources;
    vector<string> terminuses;

public:

    /**
    * @brief Constructor for Graph
    **/
    Network();

    /**
    * @brief Copy constructor for Graph
    **/
    Network(const Network&);

    /**
    * @brief Destructor for Graph
    **/
    ~Network();

    /**
     * @brief Function that adds a node.
     * @param tag Name for the node.
     * @param capacity Maximum flow that can pass through the node
     * @param restriction Minimum flow that can pass through the node
     * @return Whether the node was inserted.
     **/
    bool add_node(string tag, float capacity=numeric_limits<float>::infinity(), float restriction=0, float production=0);

    /**
    * @brief Function that adds an edge.
    * @param node1_tag Name for the first node.
    * @param node2_tag Name for the first node.
    * @param edge_tag Name for the edge.
    * @param capacity Maximum flow that can pass through the edge
    * @param restriction Minimum flow that can pass through the edge
    * @return Whether the edge was inserted.
    **/
    bool add_edge(string node1_tag, string node2_tag, string edge_tag, float capacity=numeric_limits<float>::infinity(), float restriction=0, float flow=0, float cost=0);

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
    NetworkNode* get_node(string tag);

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
    Network& operator=(const Network &);

    bool ford_fulkerson(float &total_flow, float target_flow = numeric_limits<float>::infinity());

    void set_source(string tag);
    
    void set_terminus(string tag);

    void remove_source(string tag);
    
    void remove_terminus(string tag);

    void update_flow(unordered_map<string, float> &edge_flow);

    vector<string> get_sources();

    vector<string> get_terminuses();

    LinkedList<NetworkNode> get_nodes();

    bool general_ford_fulkerson(float &total_flow, float target_flow=numeric_limits<float>::infinity());
    
    void sum_edge_capacity(string &node1_tag, string &node2_tag, float restriction);

    bool get_edge(string node1_tag, string node2_tag, string edge_tag, NetworkEdge &edge);

    bool set_edge(string node1_tag, string node2_tag, string edge_tag, float new_capacity, float new_restriction, float new_flow);
    
    float node_flow_in(NetworkNode* p);

    float current_flow();

    float current_cost();

    bool primal_minimum_cost_flow(float target_flow);

    vector<string> expand_restricted_nodes();

    void restore_restricted_nodes(vector<string> &restricted_nodes);

    void marginal_network(Digraph &n);

    bool get_factible_flow(bool replace_network=true);

    bool add_super_nodes(vector<string> &sources, vector<string> &terminuses);

    void remove_super_nodes(vector<string> &sources, vector<string> &terminuses);

    void to_digraph(Digraph &D);

    bool dual_minimum_cost_flow(float target_flow);

    bool simplex(float &cost);

    void to_digraph_simplex(Digraph &D);
    
    bool general_simplex(float &cost);

    float get_big_m();
    
    float in_flow(NetworkNode *n);
    
    float out_flow(NetworkNode *n);    
};

#endif // DIGRAPH_H_INCLUDED