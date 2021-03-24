/*
Filename: Digraph.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 17/01/2021
Description: Functions of the implementetion of a Digraph
*/
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <limits>
#include <queue>
#include "graphstructs.h"
#include "linkedlist.h"
#include "digraph.h"
#include "dijkstraheap.h"

using std::cout;
using std::endl;
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::priority_queue;
using std::stack;
using std::greater;
using std::numeric_limits;

Digraph::Digraph() : num_edges(0), num_nodes(0), weighted(0), weight(0) {}

//**********************************************************************//

Digraph::Digraph(const Digraph &G) : num_edges(0), num_nodes(0), weighted(0), weight(0) {
    *this = G;
}

//**********************************************************************//

Digraph& Digraph::operator=(const Digraph &G) {
    if (this == &G) return *this;
    // set to keep already added nodes
    unordered_set<string> added_edges;
    clear();
    // add each node
    for (ListNode<DigraphNode> *p=G.nodes.start; p; p=p->next) {
        add_node((p->value).tag);
    }
    // iterate edges for each node
    for (ListNode<DigraphNode> *p=G.nodes.start; p; p=p->next) {
        for (ListNode<DigraphEdge> *q = (p->value).inedges->start; q; q=q->next) {
            if (added_edges.find((q->value).tag) == added_edges.end()) {
                // if tag not already added
                add_edge((q->value).origin->tag, (p->value).tag, (q->value).tag, (q->value).weight);
                added_edges.insert((q->value).tag);
            }
        }
        for (ListNode<DigraphEdge> *q = (p->value).outedges->start; q; q=q->next) {
            if (added_edges.find((q->value).tag) == added_edges.end()) {
                // if tag not already added
                add_edge((p->value).tag, (q->value).dest->tag, (q->value).tag, (q->value).weight);
                added_edges.insert((q->value).tag);
            }
        }
    }
    return *this;
}

//**********************************************************************//

Digraph::~Digraph() {
    clear();
}

//**********************************************************************//

void Digraph::set_type(int t) {
    weighted = t;
}

//**********************************************************************//

float Digraph::get_weight() {
    return weight;
}

//**********************************************************************//

bool Digraph::add_node(string tag) {
    if (!find_node(tag)) { // If tag found
        DigraphNode new_node = {
            .tag = tag,
            .inedges = new LinkedList<DigraphEdge>,
            .outedges = new LinkedList<DigraphEdge>
        };
        nodes.add(new_node);
        num_nodes++;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Digraph::add_edge(string node1_tag, string node2_tag, string edge_tag, float weight) {
    //find both nodes
    DigraphNode* p1 = get_node(node1_tag); //origin node
    DigraphNode* p2 = get_node(node2_tag); // destination node
    if (!find_edge(edge_tag) && p1 && p2) {
        DigraphEdge new_edge = { // Link them using the Digraph edge as value
            .tag = edge_tag,
            .origin = p1,
            .dest = p2,
            .weight = weight
        };
        p1->outedges->add(new_edge);
        p2->inedges->add(new_edge);
        num_edges++;
        this->weight += weight;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Digraph::remove_node(string tag) {
    DigraphNode* p = get_node(tag);
    if (p) {
        DigraphEdge tmp_edge; // pivot edge to delete edges
        for (DigraphEdge& edge: *(p->inedges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from inedges
            edge.origin->outedges->remove(tmp_edge);
        }
        delete p->inedges;
        for (DigraphEdge& edge: *(p->outedges)) {
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

bool Digraph::remove_edge(string node1_tag, string node2_tag) {
    DigraphNode* p1 = get_node(node1_tag); // origin node
    DigraphNode* p2 = get_node(node2_tag); // destination node
    if (!p1 || !p2) return false;
    bool found = false;
    for (DigraphEdge& edge: *(p1->outedges)) {
        if (edge.dest == p2) {
            DigraphEdge tmp_edge;
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

bool Digraph::remove_edge(string tag) {
    bool deleted = false;
    DigraphEdge tmp_edge;
    tmp_edge.tag = tag;
    for (DigraphNode& node: nodes) {
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

bool Digraph::find_node(string tag) {
    return (bool) get_node(tag);
}

//**********************************************************************//

DigraphNode* Digraph::get_node(string tag) {
    DigraphNode temp_node;
    temp_node.tag = tag;
    auto list_node = nodes.find(temp_node);
    if (list_node) return &(list_node->value);
    return nullptr;
}

//**********************************************************************//

bool Digraph::find_edge(string node1_tag, string node2_tag) {
    DigraphNode* node1_ptr = get_node(node1_tag); // origin node
    DigraphNode* node2_ptr = get_node(node2_tag); // destination node
    if (node1_ptr && node2_ptr) {
        for (DigraphEdge& edge: *(node1_ptr->outedges)) {
            if (edge.dest == node2_ptr) return true;
        }
    }
    return false;
}

//**********************************************************************//

bool Digraph::find_edge(string tag) {
    DigraphEdge tmp_edge;
    tmp_edge.tag = tag;
    for (DigraphNode& node: nodes) {
        if (node.inedges->find(tmp_edge)) return true;
        if (node.outedges->find(tmp_edge)) return true;
    }
    return false;
}

//**********************************************************************//

int Digraph::in_node_degree(string tag) {
    DigraphNode* temp_node = get_node(tag);
    LinkedList<DigraphEdge> *inedge_list = temp_node->inedges;

    return (*inedge_list).Length();
}

//**********************************************************************//

int Digraph::out_node_degree(string tag) {
    DigraphNode* temp_node = get_node(tag);
    LinkedList<DigraphEdge> *outedge_list = temp_node->outedges;

    return (*outedge_list).Length();
}


//**********************************************************************//

int Digraph::node_count() {
    return nodes.Length();
}

//**********************************************************************//

int Digraph::edge_count() {
    int total = 0;
    for (DigraphNode node: nodes) {
        total += node.inedges->Length();
        total += node.outedges->Length();
    }
    return total / 2;
}

//**********************************************************************//

bool Digraph::remove_edges(string tag) {
    DigraphNode* p = get_node(tag);
    if (p) {
        DigraphEdge tmp_edge; // pivot edge to delete edges
        for (DigraphEdge& edge: *(p->inedges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.origin->outedges->remove(tmp_edge);
        }
        p->inedges->clear();
        for (DigraphEdge& edge: *(p->outedges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.dest->inedges->remove(tmp_edge);
        }
        p->outedges->clear();
        return true;
    }
    return false;
}

//**********************************************************************//

void Digraph::clear() {
    for (DigraphNode node: nodes) {
        delete node.inedges;
        delete node.outedges;
    }
    nodes.clear();
}

//**********************************************************************//

void Digraph::print() {
    cout << endl << "*****  GRAPH *****" << endl;
    for (DigraphNode& node: nodes) {
        cout << node << " IN: ";
        for (DigraphEdge& edge: *(node.inedges)) {
            cout << edge << " " << *(edge.origin);
            if(weighted) cout << " w: " << edge.weight;
            cout << " | ";
        }
        cout << endl << node << " OUT: ";
        for (DigraphEdge& edge: *(node.outedges)) {
            cout << edge << " " << *(edge.dest);
            if(weighted) cout << " w: " << edge.weight;
            cout << " | " ;
        }
        cout << endl << "-------------------------------------" << endl;
    }
    if (weighted){
         cout << "weight : " << weight << endl;
    }
    
}

//**********************************************************************//

inline DigraphNode* ancestor(DigraphNode *p) {
    return (*(p->inedges->begin())).origin;
}

inline DigraphNode* descendant(DigraphNode *p) {
    return (*(p->outedges->begin())).dest;
}

//**********************************************************************//

bool Digraph::dijkstra(string initial_tag, Digraph &tree, vector<string> &cycle, float &cycle_len, string destination_tag, bool optimize) {
    enum {non_visited, visited, permanent};
    unordered_map<string, DijkstraAux> label;

    DigraphNode *initial;
    initial = get_node(initial_tag);

    unordered_map<string, int> nodes_states;
    DijkstraHeap p;     // Priority queue

    for (DigraphNode &n: nodes) {
        nodes_states.insert({n.tag, non_visited});
    }

    DijkstraAux dInitial;
    dInitial.set(*initial, *initial, 0, 0, initial->tag);
    p.push(dInitial);

    while (!p.is_empty()){
        DijkstraAux current;

        current = p.pop();

        // Update state
        nodes_states[current.node->tag] = permanent;

        if (destination_tag != "" && current.node->tag == destination_tag) return true;

        for (DigraphEdge &edge : *(current.node->outedges)) {
            if (nodes_states[edge.dest->tag] == permanent) continue;
            
            else if (nodes_states[edge.dest->tag] == non_visited) {
                nodes_states[edge.dest->tag] = visited;
                DijkstraAux d;
                d.set(*(edge.dest), *(current.node), 
                    current.accumulated_weight + edge.weight, edge.weight, edge.tag);
                p.push(d);

            } else {
                if (p.get_priority(edge.dest->tag) > current.accumulated_weight + edge.weight) {
                    // Update priority
                    DijkstraAux d;
                    d.set(*(edge.dest), *(current.node), 
                        current.accumulated_weight + edge.weight, edge.weight, edge.tag);
                    p.update_priority(d);
                }
            }
        }

        // Add to tree

        tree.add_node(current.node->tag);
        tree.add_node(current.predecessor->tag);

        tree.add_edge(current.predecessor->tag, current.node->tag, 
                        current.edge_tag, current.edge_weight);
        label.insert({current.node->tag, current});

    }

    if (tree.num_nodes != num_nodes) return false;

    tree.remove_edge(initial_tag, initial_tag);
    
    if (!optimize) return true;

    // Optimization step
    while (true) {
        DigraphNode *i = nullptr, *j = nullptr;
        float aux_weight, dl;
        string aux_tag;

        bool found_improv = false; // flag
        for (DigraphNode n : nodes) {
            for (DigraphEdge e : *(n.outedges)) {
                // Every edge not in arborescence
                if (!tree.find_edge(n.tag, e.dest->tag)) {
                    if (label[n.tag].accumulated_weight + e.weight < label[e.dest->tag].accumulated_weight) {
                        i = &n;
                        j = e.dest;
                        aux_tag = e.tag;
                        aux_weight = e.weight;
                        found_improv = true;
                        break;
                    }
                }
            }
            if (found_improv) break;
        }

        // if no improvement found, break and finalize
        if (!found_improv) break;
        
        // total improvement in each node
        dl = label[j->tag].accumulated_weight - (label[i->tag].accumulated_weight + aux_weight);

        // find arborescence pointers
        DigraphNode *tree_i = tree.get_node(i->tag);
        DigraphNode *tree_j = tree.get_node(j->tag);

        // look for j in every ancestor of i in the arborescence
        cycle.clear();
        for (DigraphNode* p = tree_i; p->inedges->Length() > 0; p = ancestor(p)) {
            cycle.push_back(p->tag);
            if (p == tree_j) {
                cycle_len = -dl;
                return false;
            }
        }

        // replace edge
        tree.remove_edge(ancestor(tree_j)->tag, tree_j->tag);
        tree.add_edge(tree_i->tag, tree_j->tag, aux_tag, aux_weight);

        // update j label
        label[j->tag].set(*j, *i, label[j->tag].accumulated_weight - dl, aux_weight, aux_tag);

        // update every descendant
        DigraphNode *p = tree_j;
        while (p->outedges->Length() > 0) {
            // take first outgoing node
            p = descendant(p);
            label[p->tag].accumulated_weight -= dl;
        }
    }
    return true;
}