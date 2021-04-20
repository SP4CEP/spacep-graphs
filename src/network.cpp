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

#include "graphstructs.h"
#include "linkedlist.h"
#include "network.h"

using std::cout;
using std::endl;
using std::reverse;
using std::string;
using std::unordered_set;
using std::unordered_map;

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
                add_edge((q->value).origin->tag, (p->value).tag, (q->value).tag, (q->value).capacity, (q->value).restriction);
                added_edges.insert((q->value).tag);
            }
        }
        for (ListNode<NetworkEdge> *q = (p->value).outedges->start; q; q=q->next) {
            if (added_edges.find((q->value).tag) == added_edges.end()) {
                // if tag not already added
                add_edge((p->value).tag, (q->value).dest->tag, (q->value).tag, (q->value).capacity, (q->value).restriction);
                added_edges.insert((q->value).tag);
            }
        }
    }
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

bool Network::add_edge(string node1_tag, string node2_tag, string edge_tag, float capacity, float restriction) {
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
            .flow = 0
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

//**********************************************************************//


void Network::ford_fulkerson() {
    unordered_map<string, FordFulkersonTag> tag;
    unordered_map<string, float> edge_flow;

    // Flujo inicial en ceros
    for (NetworkNode node : nodes) {
        for (NetworkEdge edge : *(node.outedges)) {
            edge_flow.insert({edge.tag, 0});
        }
    }

    while (true) {
        // Encontrar un flujo factible
        // Establece el primero
        ;
    }
    


}

void Network::update_flow(unordered_map<string, float> edge_flow) {
    for (NetworkNode node: nodes) {
        for (NetworkEdge& edge : *(node.outedges)) 
            edge.flow = edge_flow[edge.tag];
        
        for (NetworkEdge& edge : *(node.inedges)) 
            edge.flow = edge_flow[edge.tag];
    }
}
