/*
Filename: Network.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 17/01/2021
Description: Functions of the implementetion of a Network
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <limits>

#include "graphstructs.h"
#include "linkedlist.h"
#include "network.h"

using std::cout;
using std::endl;
using std::reverse;
using std::min;
using std::to_string;
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::numeric_limits;

Network::Network() : num_edges(0), num_nodes(0) {
}

//**********************************************************************//

Network::Network(const Network &G) : num_edges(0), num_nodes(0) {
    *this = G;
}

//**********************************************************************//

Network& Network::operator=(const Network &G) {
    if (this == &G) return *this;
    // set to keep already added nodes
    unordered_set<string> added_edges;
    clear();
    // add each node
    for (ListNode<NetworkNode> *p=G.nodes.start; p; p=p->next) {
        add_node((p->value).tag, (p->value).capacity, (p->value).restriction);
    }
    // iterate edges for each node
    for (ListNode<NetworkNode> *p=G.nodes.start; p; p=p->next) {
        for (ListNode<NetworkEdge> *q = (p->value).inedges->start; q; q=q->next) {
            if (added_edges.find((q->value).tag) == added_edges.end()) {
                // if tag not already added
                add_edge((q->value).origin->tag, (p->value).tag, (q->value).tag, (q->value).capacity, (q->value).restriction, (q->value).flow);
                added_edges.insert((q->value).tag);
            }
        }
        for (ListNode<NetworkEdge> *q = (p->value).outedges->start; q; q=q->next) {
            if (added_edges.find((q->value).tag) == added_edges.end()) {
                // if tag not already added
                add_edge((p->value).tag, (q->value).dest->tag, (q->value).tag, (q->value).capacity, (q->value).restriction, (q->value).flow);
                added_edges.insert((q->value).tag);
            }
        }
    }
    this->sources = G.sources;
    this->terminuses = G.terminuses;
    return *this;
}

//**********************************************************************//

Network::~Network() {
    clear();
}

//**********************************************************************//

bool Network::add_node(string tag, float capacity, float restriction) {
    if (!find_node(tag)) { // If tag found
        NetworkNode new_node = {
            .tag = tag,
            .inedges = new LinkedList<NetworkEdge>,
            .outedges = new LinkedList<NetworkEdge>,
            .capacity = capacity,
            .restriction = restriction,
        };
        nodes.add(new_node);
        num_nodes++;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Network::add_edge(string node1_tag, string node2_tag, string edge_tag, float capacity, float restriction, float flow) {
    //find both nodes
    NetworkNode* p1 = get_node(node1_tag); //origin node
    NetworkNode* p2 = get_node(node2_tag); // destination node
    if (!find_edge(edge_tag) && p1 && p2) {
        NetworkEdge new_edge = { // Link them using the Network edge as value
            .tag = edge_tag,
            .origin = p1,
            .dest = p2,
            .capacity = capacity,
            .restriction = restriction,
            .flow = flow
        };
        p1->outedges->add(new_edge);
        p2->inedges->add(new_edge);
        num_edges++;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Network::remove_node(string tag) {
    NetworkNode* p = get_node(tag);
    if (p) {
        NetworkEdge tmp_edge; // pivot edge to delete edges
        for (NetworkEdge& edge: *(p->inedges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from inedges
            edge.origin->outedges->remove(tmp_edge);
        }
        delete p->inedges;
        for (NetworkEdge& edge: *(p->outedges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.dest->inedges->remove(tmp_edge);
        }
        delete p->outedges;
        nodes.remove(*p);
        num_nodes--;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Network::remove_edge(string node1_tag, string node2_tag) {
    NetworkNode* p1 = get_node(node1_tag); // origin node
    NetworkNode* p2 = get_node(node2_tag); // destination node
    if (!p1 || !p2) return false;
    bool found = false;
    for (NetworkEdge& edge: *(p1->outedges)) {
        if (edge.dest == p2) {
            NetworkEdge tmp_edge;
            tmp_edge.tag = edge.tag;
            p1->outedges->remove(tmp_edge);
            p2->inedges->remove(tmp_edge);
            found = true;
            break;
        }
    }
    if (found) {
        num_edges--;
    }
    return found;
}

//**********************************************************************//

bool Network::remove_edge(string tag) {
    bool deleted = false;
    NetworkEdge tmp_edge;
    tmp_edge.tag = tag;
    for (NetworkNode& node: nodes) {
        //OUT
        if (node.outedges->remove(tmp_edge)) {
            if (deleted) break; // both edges in both nodes already deleted
            else if (node.outedges->remove(tmp_edge)) {
                break;
            }
            deleted = true;
        // IN
        }
        if (node.inedges->remove(tmp_edge)) {
            if (deleted) break; // both edges in both nodes already deleted
            else if (node.inedges->remove(tmp_edge)) {
                break;
            }
            deleted = true;
        }
    }
    if (deleted) {
        num_edges--;
    }
    return deleted;
}

//**********************************************************************//

bool Network::find_node(string tag) {
    return (bool) get_node(tag);
}

//**********************************************************************//

NetworkNode* Network::get_node(string tag) {
    NetworkNode temp_node;
    temp_node.tag = tag;
    auto list_node = nodes.find(temp_node);
    if (list_node) return &(list_node->value);
    return nullptr;
}

//**********************************************************************//

bool Network::find_edge(string node1_tag, string node2_tag) {
    NetworkNode* node1_ptr = get_node(node1_tag); // origin node
    NetworkNode* node2_ptr = get_node(node2_tag); // destination node
    if (node1_ptr && node2_ptr) {
        for (NetworkEdge& edge: *(node1_ptr->outedges)) {
            if (edge.dest == node2_ptr) return true;
        }
    }
    return false;
}

//**********************************************************************//

bool Network::find_edge(string tag) {
    NetworkEdge tmp_edge;
    tmp_edge.tag = tag;
    for (NetworkNode& node: nodes) {
        if (node.inedges->find(tmp_edge)) return true;
        if (node.outedges->find(tmp_edge)) return true;
    }
    return false;
}

//**********************************************************************//

int Network::in_node_degree(string tag) {
    NetworkNode* temp_node = get_node(tag);
    LinkedList<NetworkEdge> *inedge_list = temp_node->inedges;

    return (*inedge_list).Length();
}

//**********************************************************************//

int Network::out_node_degree(string tag) {
    NetworkNode* temp_node = get_node(tag);
    LinkedList<NetworkEdge> *outedge_list = temp_node->outedges;

    return (*outedge_list).Length();
}


//**********************************************************************//

int Network::node_count() {
    return nodes.Length();
}

//**********************************************************************//

int Network::edge_count() {
    int total = 0;
    for (NetworkNode node: nodes) {
        total += node.inedges->Length();
        total += node.outedges->Length();
    }
    return total / 2;
}

//**********************************************************************//

bool Network::remove_edges(string tag) {
    NetworkNode* p = get_node(tag);
    if (p) {
        NetworkEdge tmp_edge; // pivot edge to delete edges
        for (NetworkEdge& edge: *(p->inedges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.origin->outedges->remove(tmp_edge);
        }
        p->inedges->clear();
        for (NetworkEdge& edge: *(p->outedges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.dest->inedges->remove(tmp_edge);
        }
        p->outedges->clear();
        return true;
    }
    return false;
}

//**********************************************************************//

void Network::clear() {
    for (NetworkNode node: nodes) {
        delete node.inedges;
        delete node.outedges;
    }
    nodes.clear();
}

//**********************************************************************//

void Network::print() {
    cout << endl << "*****  NETWORK *****" << endl;
    for (NetworkNode& node: nodes) {
        cout << node << " (" << node.restriction << ", " << node.capacity << ") " << " IN: ";
        for (NetworkEdge& edge: *(node.inedges)) {
            cout << edge << " " << *(edge.origin) << " (" << edge.flow << ", " << edge.restriction << ", " << edge.capacity << ")";
            cout << " | ";
        }
        cout << endl << node << " (" << node.restriction << ", " << node.capacity << ") " << " OUT: ";
        for (NetworkEdge& edge: *(node.outedges)) {
            cout << edge << " " << *(edge.dest) << " (" << edge.flow << ", " << edge.restriction << ", " << edge.capacity << ")";
            cout << " | " ;
        }
        cout << endl << "-------------------------------------" << endl;
    }
}

//**********************************************************************//

inline NetworkNode* ancestor(NetworkNode *p) {
    return (p->inedges->Length() > 0 ? (*(p->inedges->begin())).origin : nullptr);
}

inline NetworkNode* descendant(NetworkNode *p) {
    return (p->outedges->Length() > 0 ? (*(p->outedges->begin())).dest : nullptr);
}


//**********************************************************************//

void Network::set_source(string tag){
    sources.push_back(tag);
}

void Network::set_terminus(string tag){
    terminuses.push_back(tag);
}

void Network::remove_source(string tag){
    int position;
    for (position = 0; position < tag.length(); position++) {
        if (sources[position] == tag)
            break;
    }
    sources.erase(sources.begin() + position);
}

void Network::remove_terminus(string tag){
    int position;
    for (position = 0; position < tag.length(); position++) {
        if (terminuses[position] == tag)
            break;
    }
    terminuses.erase(terminuses.begin() + position);
}

//**********************************************************************//

bool Network::ford_fulkerson(float &total_flow) {
    unordered_map<string, FordFulkersonTag> tag;
    unordered_map<string, float> edge_flow;
    NetworkNode* source;
    NetworkNode* terminus;
    

    if (sources.size() != 1 || terminuses.size() != 1)
        return false;
    
    source = get_node(sources[0]);
    terminus = get_node(terminuses[0]);
    
    // Set initial total flow as the flow from source
    total_flow = 0;
    for (NetworkEdge &e : *(source->outedges)) {
        total_flow += e.flow;
    }

    // Initial flow
    for (NetworkNode node : nodes) {
        for (NetworkEdge edge : *(node.outedges)) {
            edge_flow.insert({edge.tag, edge.flow});
        }
    }

    while (true) {
        // flag to see if terminus node was reached
        bool found_terminus = false;
        queue<NetworkNode*> examine_q;

        // Find factible flow. Set source
        FordFulkersonTag aux(source, numeric_limits<float>::infinity(), false, "");
        tag.insert({source->tag, aux});
        examine_q.push(source);

        while (!found_terminus && !examine_q.empty()) {
            // Select a node to examine
            NetworkNode *j = examine_q.front();
            examine_q.pop();

            // Positive incident edges
            for (NetworkEdge e : *(j->outedges)) {
                // If node not tagged yet and flow < capacity
                if (tag.find(e.dest->tag) == tag.end() && edge_flow[e.tag] < e.capacity) {
                    FordFulkersonTag new_tag(j, min(tag[j->tag].flow, 
                                                    e.capacity - edge_flow[e.tag]), false, e.tag);
                    tag.insert({e.dest->tag, new_tag});
                    examine_q.push(e.dest);
                    if (e.dest == terminus) {
                        found_terminus = true;
                        break;
                    }
                }
            }
            
            if (found_terminus) break;

            // Negative incident edges
            for (NetworkEdge e : *(j->inedges)) {
                // If node not tagged yet and flow > 0
                if (tag.find(e.origin->tag) == tag.end() && edge_flow[e.tag] - e.restriction > 0)
                {
                    FordFulkersonTag new_tag(j, min(tag[j->tag].flow, 
                                                    edge_flow[e.tag] - e.restriction), true, e.tag);
                    tag.insert({e.origin->tag, new_tag});
                    examine_q.push(e.origin);
                    if (e.origin == terminus) {
                        found_terminus = true;
                        break;
                    }
                }
            }
        }

        if (!found_terminus) {
            // Optimal flow already found. Return.
            break;
        }

        // Update optimal flow. 
        float delta = tag[terminus->tag].flow;
        total_flow += delta;

        // print info
        //cout << "Cadena aumentante encontrada con delta " << delta << ": " << endl;
        //for (NetworkNode *x = terminus; x != source; x = tag[x->tag].predecessor) {
        //    cout << x->tag << " ";
        //}
        //cout << source->tag << endl;

        // update flow in every single edge. Begin in terminus, end at source.
        for (NetworkNode *x = terminus; x != tag[x->tag].predecessor; x = tag[x->tag].predecessor) {
            // if reversed substract, else, add
            edge_flow[tag[x->tag].edge_tag] += delta * (tag[x->tag].reverse ? -1 : 1);
        }

        // clear node tags to find another flow
        tag.clear();
    }

    update_flow(edge_flow);
    return true;
}

//***************************************************************//

void Network::sum_edge_capacity(string &node1_tag, string &node2_tag, float restriction) {
    NetworkNode* node1_ptr = get_node(node1_tag); // origin node
    NetworkNode* node2_ptr = get_node(node2_tag); // destination node

    if (node1_ptr && node2_ptr) {
        for (NetworkEdge& edge: *(node1_ptr->outedges)) {
            if (edge.dest == node2_ptr) {
                edge.capacity += restriction;
                break;
            } 
        }
        for (NetworkEdge& edge: *(node2_ptr->inedges)) {
            if (edge.origin == node1_ptr) {
                edge.capacity += restriction;
                return;
            } 
        }
    }
}

//***************************************************************//

bool Network::get_edge(string node1_tag, string node2_tag, NetworkEdge &edge) {
    NetworkNode* node1_ptr = get_node(node1_tag);
    NetworkNode* node2_ptr = get_node(node2_tag);
    if (node1_ptr && node2_ptr) {
        for (NetworkEdge &e: *(node1_ptr->outedges)) {
            if (e.dest == node2_ptr) {
                edge = e;
                return true;
            }
        }
    }
    return false;
}

/**********************************************************/

bool Network::set_edge(string node1_tag, string node2_tag, float new_capacity, float new_restriction, float new_flow) {
    NetworkNode *node1_ptr = get_node(node1_tag);
    NetworkNode *node2_ptr = get_node(node2_tag);
    if (node1_ptr && node2_ptr) {
        for (NetworkEdge &e: *(node1_ptr->outedges)) {
            if (e.dest == node2_ptr) {
                e.capacity = new_capacity;
                e.restriction = new_restriction;
                e.flow = new_flow;
                break;
            }
        }

        for (NetworkEdge &e: *(node2_ptr->inedges)) {
            if (e.origin == node1_ptr) {
                e.capacity = new_capacity;
                e.restriction = new_restriction;
                e.flow = new_flow;
                break;
            }

        }
    } else {
        return false;
    }
    return true;
}

/***********************************************************/

bool Network::general_ford_fulkerson(float &total_flow) {
    bool multiple_sources=false, multiple_terminuses=false, node_restrictions=false, edge_restrictions=false;
    Network N_aux = *this;
    vector<string> restricted_nodes;

    /**
     * Three cases:
     * 1) multiple sources and terminuses
     * 2) minimum restrictions in edges
     * 3) minimum and maximum restrictions in nodes
     **/
    
    string super_terminus_tag = "super_terminus";
    string super_source_tag = "super_source";

    // Resolve multiple sources
    if (sources.size() > 1) {
        multiple_sources = true;
        N_aux.add_node(super_source_tag);
        N_aux.set_source(super_source_tag);
        for (string s : sources) {
            N_aux.remove_source(s);
            N_aux.add_edge(super_source_tag, s, super_source_tag + "_to_" + s);
        }
    }
    
    // Resolve multiple terminuses
    if (terminuses.size() > 1) {
        multiple_terminuses = true;
        N_aux.add_node(super_terminus_tag);
        N_aux.set_terminus(super_terminus_tag);
        for (string t : terminuses) {
            N_aux.remove_terminus(t);
            N_aux.add_edge(t, super_terminus_tag, t + "_to_" + super_terminus_tag);
        }
    }

    //cout << "Aquí se pusieron super source y super terminus" << endl;
    //N_aux.print();

    // Resolve nodes with restrictions
    for (NetworkNode &n : nodes) {
        // has restriction > 0 or capacity < inf
        if (n.restriction > 0 || n.capacity < numeric_limits<float>::infinity()) {
            // update flag
            node_restrictions = true;
            restricted_nodes.push_back(n.tag);
            // tag for the dest node to create
            string aux_node_tag = n.tag + "_outedges";
            // add the new node and connect with n
            N_aux.add_node(aux_node_tag);
            N_aux.add_edge(n.tag, aux_node_tag, aux_node_tag + "_node_restriction_edge", n.capacity, n.restriction);
            // update node capacity and restriction in auxiliar net
            NetworkNode *p = N_aux.get_node(n.tag);
            p->restriction = 0;
            p->capacity = numeric_limits<float>::infinity();
            // add every outedge to the new created node, and delete from original node
            for (NetworkEdge &e : *(n.outedges)) {
                N_aux.remove_edge(n.tag, e.dest->tag);
                N_aux.add_edge(aux_node_tag, e.dest->tag, e.tag+"'", e.capacity, e.restriction);
            }
        }
    }
    
    //cout << "Aquí se ponen nodos partidos a la mitad xD" << endl;
    //N_aux.print();

    // Resolve remaining edges with minimum restriction
    string prev_source, prev_terminus;
    unordered_map<string, float> edges_with_restrictions;
    int i = 0;
    for (NetworkNode &n : N_aux.nodes) {
        for (NetworkEdge &e : *(n.outedges)) {
            if (e.restriction > 0) {
                edges_with_restrictions.insert({e.tag, e.restriction});
                if (!edge_restrictions) {
                    // Create new source and terminus for edges with restrictions
                    N_aux.add_node(N_aux.sources[0] + "'");
                    N_aux.add_node(N_aux.terminuses[0] + "'");
                    // Connect source to terminus and backwards
                    N_aux.add_edge(N_aux.sources[0], N_aux.terminuses[0], "source_to_terminus");
                    N_aux.add_edge(N_aux.terminuses[0], N_aux.sources[0], "terminus_to_source");
                    // Save previous values of source and terminus
                    prev_source = N_aux.sources[0];
                    prev_terminus = N_aux.terminuses[0];
                    // Remove current source and terminus
                    N_aux.remove_source(prev_source);
                    N_aux.remove_terminus(prev_terminus);
                    // Set new source and terminus
                    N_aux.set_source(prev_source + "'");
                    N_aux.set_terminus(prev_terminus + "'");
                    // indicate there exist edge restrictions
                    edge_restrictions = true;
                }
                // If edge not added yet (source' to dest)
                if (!N_aux.add_edge(N_aux.sources[0], e.dest->tag, "source'_to_" + e.dest->tag, e.restriction, 0)) {
                    // Edge already exists
                    N_aux.sum_edge_capacity(N_aux.sources[0], e.dest->tag, e.restriction);
                }
                
                // If edge not added yet (origin to terminus')
                if (!N_aux.add_edge(e.origin->tag, N_aux.terminuses[0], e.origin->tag + "_to_terminus'", e.restriction, 0)) {
                    // Edge already exists
                    N_aux.sum_edge_capacity(e.origin->tag, N_aux.terminuses[0], e.restriction);
                }

                N_aux.set_edge(e.origin->tag, e.dest->tag, e.capacity - e.restriction, 0, e.flow);
            }
        }
    }


    if (edge_restrictions) {

        // Find a factible flow
        N_aux.ford_fulkerson(total_flow);

        //cout << "Aquí se resuleven aristas con mínimos." << endl;
        //N_aux.print();

        // Restore edge with minimum restrictions
        NetworkNode* temp_terminus = N_aux.get_node(N_aux.terminuses[0]);
        // For every entrant node
        for (NetworkEdge &entrant : *(temp_terminus->inedges)) {
            // distribute flow among 
            float available_flow = entrant.flow;
            NetworkNode* p = entrant.origin;
            // for every outedge of the node that enters in temp terminus
            for (NetworkEdge &e : *(p->outedges)) {
                // If edge had restrictions before
                if (edges_with_restrictions.find(e.tag) != edges_with_restrictions.end()) {
                    float restored_cap, restored_rest, restored_flow;
                    // get restores capacity and restriction values
                    restored_rest = edges_with_restrictions[e.tag];
                    restored_cap = e.capacity + restored_rest;
                    // if not enough available flow return
                    if (restored_rest > available_flow)
                        return false;
                    // get restored flow
                    restored_flow = e.flow + restored_rest;
                    //update values
                    N_aux.set_edge(e.origin->tag, e.dest->tag, restored_cap, restored_rest, restored_flow);
                    // discount to the remaining available flow
                    available_flow -= restored_rest;
                }
            }
        }

        // remove temp terminus and source
        N_aux.remove_node(N_aux.sources[0]);
        N_aux.remove_node(N_aux.terminuses[0]);
        N_aux.remove_source(N_aux.sources[0]);
        N_aux.remove_terminus(N_aux.terminuses[0]);

        // add original term and src
        N_aux.set_source(prev_source);
        N_aux.set_terminus(prev_terminus);

        // remove connection from original source to terminus and viceversa
        N_aux.remove_edge("source_to_terminus");
        N_aux.remove_edge("terminus_to_source");

    }

    //cout << "Aquí el flujo factible de " << N_aux.current_flow() << " se ha repartido entre las aristas restringidas" << endl;
    //N_aux.print();

    N_aux.ford_fulkerson(total_flow);

    //cout << "Aquí el flujo factible se ha encontrado el flujo óptimo de: " << total_flow << endl;
    //N_aux.print();

    // Restore nodes with restrictions
    if (node_restrictions) {
        for (string node_tag : restricted_nodes) {
            // original node
            NetworkNode *node = N_aux.get_node(node_tag);
            // expanded node
            NetworkNode *node_out = N_aux.get_node(node_tag+"_outedges");
            NetworkEdge joining_edge;

            for (NetworkEdge &e : *(node_out->outedges)) {
                // remove last char
                string original_tag = e.tag.substr(0, e.tag.length()-1);
                // add edge
                N_aux.add_edge(node_tag, e.dest->tag, original_tag, e.capacity, e.restriction, e.flow);
            }

            // get the edge that joins both parts of the node
            N_aux.get_edge(node->tag, node_out->tag, joining_edge);

            // set the original values for the node's capacity and restriction
            node->capacity = joining_edge.capacity;
            node->restriction = joining_edge.restriction;

            // remove the auxiliar node
            N_aux.remove_node(node_out->tag);
        }
    }

    //cout << "Aquí se han restaurado los nodos con restricciones" << endl;
    //N_aux.print();

    // Restore multiple sources
    if (multiple_sources){
        N_aux.remove_node("super_source");
        N_aux.remove_source("super_source");
        for (string src : sources) {
            N_aux.set_source(src);
        }
    }

    // Restore multiple terminuses
    if (multiple_terminuses){
        N_aux.remove_node("super_terminus");
        N_aux.remove_terminus("super_terminus");
        for (string term : terminuses) {
            N_aux.set_terminus(term);
        }
    }

    //cout << "Aquí se han restaurado multiples sumideros y fuentes" << endl;

    // Set auxiliar as current graph
    *this = N_aux;

    return true;
}

//***************************************************************//

void Network::update_flow(unordered_map<string, float> &edge_flow) {
    for (NetworkNode node: nodes) {
        for (NetworkEdge& edge : *(node.outedges)) 
            edge.flow = edge_flow[edge.tag];
        
        for (NetworkEdge& edge : *(node.inedges)) 
            edge.flow = edge_flow[edge.tag];
    }
}

float Network::current_flow() {
    if (sources.size() != 1) return - numeric_limits<float>::infinity();
    
    float total_flow = 0;
    NetworkNode *source = get_node(sources[0]);
    
    // Set initial total flow as the flow from source
    for (NetworkEdge &e : *(source->outedges)) {
        total_flow += e.flow;
    }

    return total_flow;
}
