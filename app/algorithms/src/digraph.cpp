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
#include <algorithm>
#include <stack>
#include <string>
#include <limits>
#include <queue>

//#include <mcheck.h>

#include "graphstructs.h"
#include "linkedlist.h"
#include "digraph.h"
#include "dijkstraheap.h"
#include "matrix.h"

using std::cout;
using std::endl;
using std::reverse;
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::priority_queue;
using std::stack;
using std::greater;
using std::numeric_limits;

Digraph::Digraph() : num_edges(0), num_nodes(0), weighted(0), weight(0)
{
}

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

bool Digraph::remove_edge(const string node1_tag, const string node2_tag) {
    DigraphNode* p1 = get_node(node1_tag); // origin node
    DigraphNode* p2 = get_node(node2_tag); // destination node
    if (!p1 || !p2) return false;
    bool found = false;
    float tmp_weight;
    for (DigraphEdge& edge: *(p1->outedges)) {
        if (edge.dest == p2) {
            DigraphEdge tmp_edge;
            tmp_edge.tag = edge.tag;
            tmp_weight  = tmp_edge.weight;
            p1->outedges->remove(tmp_edge);
            p2->inedges->remove(tmp_edge);
            found = true;
            break;
        }
    }
    if (found) {
        num_edges--;
        weight -= tmp_weight;
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
    num_edges = 0;
    num_nodes = 0;
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

DigraphNode* ancestor(DigraphNode *p) {
    if (p->inedges->begin() != nullptr)
        return (*(p->inedges->begin())).origin;
    else 
        return nullptr;
}

DigraphNode* descendant(DigraphNode *p) {
    if (p->outedges->begin() != nullptr)
        return (*(p->outedges->begin())).dest;
    else 
        return nullptr;
}

DigraphEdge* ancestor_edge(DigraphNode *p) {
    if (p->inedges->begin() != nullptr)
        return &(*(p->inedges->begin()));
    else 
        return nullptr;
}

DigraphEdge* descendant_edge(DigraphNode *p) {
    if (p->outedges->begin() != nullptr)
        return &(*(p->outedges->begin()));
    else 
        return nullptr;
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

        if (destination_tag != "" && current.node->tag == destination_tag){
            tree.add_node(destination_tag);
            tree.add_edge(current.predecessor->tag, destination_tag, current.edge_tag, current.edge_weight);
            return true;
        } 

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
    
    return optimize_dijkstra(tree, cycle, cycle_len, label);
}
//**********************************************************************//


bool Digraph::optimize_dijkstra(Digraph &tree, vector<string> &cycle, float &cycle_len, unordered_map<string, DijkstraAux> &label) {
    // Optimization step
    while (true) {
        print();
        DigraphNode *i = nullptr, *j = nullptr;
        float aux_weight, dl;
        string aux_tag;

        bool found_improv = false; // flag
        for (DigraphNode &n : nodes) {
            for (DigraphEdge &e : *(n.outedges)) {
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
            if (found_improv)
                break;
        }

        // if no improvement found, break and finalize
        if (!found_improv)
            break;

        // total improvement in each node
        dl = label[j->tag].accumulated_weight - (label[i->tag].accumulated_weight + aux_weight);

        // find arborescence pointers
        DigraphNode *tree_i = tree.get_node(i->tag);
        DigraphNode *tree_j = tree.get_node(j->tag);

        cycle.clear();
        cycle.push_back(tree_i->tag);
        // Iterate over ancestor edges until start is reached (no ancestor edge returns nullptr)
        for (DigraphEdge *i_ancestor_edge = ancestor_edge(tree_i); 
             i_ancestor_edge != nullptr; 
             i_ancestor_edge = ancestor_edge(i_ancestor_edge->origin)) {
            // Add edge tag and origin tag
            cycle.push_back(i_ancestor_edge->tag);
            cycle.push_back(i_ancestor_edge->origin->tag);
            // If origin of edge is tree_j, a negative cycle has been found
            if (i_ancestor_edge->origin == tree_j) {
                cycle_len = -dl;
                // Insert edge that completes cycle
                cycle.push_back(aux_tag);
                cycle.push_back(tree_i->tag);
                // reverse to make it straightforward
                reverse(cycle.begin(), cycle.end());
                return false;
            }
        }

        //mprobe(i);

        // replace edge
        DigraphNode *tree_j_parent = ancestor(tree_j);
        string tree_j_parent_tag = tree_j_parent->tag;
        string tree_j_tag = tree_j->tag;

        tree.remove_edge(tree_j_parent_tag, tree_j_tag);
        tree.add_edge(tree_i->tag, tree_j->tag, aux_tag, aux_weight);

        tree_i = tree.get_node(i->tag);
        tree_j = tree.get_node(j->tag);

        //tree.print();

        // update j label
        label[j->tag].set(*j, *i, label[j->tag].accumulated_weight, aux_weight, aux_tag);

        // update every descendant
        DigraphNode *desc = tree_j;
        queue<DigraphNode *> nodes_to_update;
        nodes_to_update.push(desc);
        while (!nodes_to_update.empty()) {
            desc = nodes_to_update.front();
            // insert every descendant
            for (DigraphEdge &e : *(desc->outedges)) {
                nodes_to_update.push(e.dest);
            }
            label[desc->tag].accumulated_weight -= dl;
            nodes_to_update.pop();
        }
    }
    return true;
}


void Digraph::Graph2Mat(Matrix<DijkstraAux> &Floyd, unordered_map<string, int> &aux_map) {
    DijkstraAux aux;
    int ix = 0;

    for(DigraphNode& node: nodes){
        aux_map.insert({node.tag, ix});
        ix++;
    }

    for (DigraphNode& row: nodes) {
        for(DigraphNode& col: nodes){
            aux.set(&row, nullptr, numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
            Floyd[aux_map[row.tag]][aux_map[col.tag]] = aux;
        }
    }

    for (DigraphNode& node: nodes) {
        for (DigraphEdge& edge: *(node.outedges)) {
            aux.set(*(edge.dest), *(edge.origin), edge.weight, edge.weight, edge.tag);
            Floyd[aux_map[node.tag]][aux_map[edge.dest->tag]] = aux;
        }
        aux.set(node, node, 0, 0, "");
        Floyd[aux_map[node.tag]][aux_map[node.tag]] = aux;
    }
}

//**********************************************************************//

bool Digraph::floyd(Matrix<DijkstraAux> &Floyd, vector<string> &cycle, float &cycle_len, unordered_map<string, int> &tag_to_index) {
    vector<string> index_to_tag;

    Floyd.init(num_nodes, num_nodes);
    Graph2Mat(Floyd, tag_to_index);

    for (DigraphNode &n : nodes)
        index_to_tag.push_back(n.tag);

    for (int k = 0; k < num_nodes; ++k) {
        for (int i = 0; i < num_nodes; ++i) {
            for (int j = 0; j < num_nodes; ++j) {
                if (Floyd[i][j].accumulated_weight > Floyd[i][k].accumulated_weight +
                                                     Floyd[k][j].accumulated_weight) {
                    Floyd[i][j].accumulated_weight = Floyd[i][k].accumulated_weight +
                                                     Floyd[k][j].accumulated_weight;
                    Floyd[i][j].predecessor = Floyd[k][j].predecessor;
                    Floyd[i][j].edge_tag = Floyd[k][j].edge_tag;
                    Floyd[i][j].edge_weight = Floyd[k][j].edge_weight;
                    
                    if (i == j) {
                        // Obtain cycle
                        cycle_len = Floyd[i][j].accumulated_weight;
                        cycle.clear();
                        // first add node i and its predecessor edge
                        int i_node = i;
                        cycle.push_back(index_to_tag[i_node]);
                        cycle.push_back(Floyd[i][i_node].edge_tag);
                        //jump to next predecessor tag
                        i_node = tag_to_index[Floyd[i][i_node].predecessor->tag];
                        //until i is reached again
                        while (i_node != i) {
                            // first add node and its predecessor edge
                            cycle.push_back(index_to_tag[i_node]);
                            cycle.push_back(Floyd[i][i_node].edge_tag);
                            //jump to next predecessor tag
                            i_node = tag_to_index[Floyd[i][i_node].predecessor->tag];
                        }
                        // Add node i again to complete cycle
                        cycle.push_back(cycle[0]);
                        // Reverse to make it straightforward
                        reverse(cycle.begin(), cycle.end());
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

//**********************************************************************//

void Digraph::printMatrix(Matrix<DijkstraAux> F){
    int i = 0;
    cout << endl << "*****  MATRIX *****" << endl;
    cout << "\t";
    for(DigraphNode& node: nodes){
        cout << "  *" << node << "* \t|\t";
    }
    for(DigraphNode& node: nodes){
       cout << endl << "*" << node << "* |\t"; 
       for(int j=0; j<num_nodes; j++){
           if(F[i][j].predecessor){
            cout << " (" << F[i][j] << ") |\t";
           }else{
              cout << " (-, ∞) |\t"; 
           }
        }
        i++;
    }
    cout << endl;
}

LinkedList<DigraphNode> Digraph::get_nodes(){
    return nodes;
}

bool Digraph::get_edge(string node1_tag, string node2_tag, DigraphEdge &edge) {
    DigraphNode* node1_ptr = get_node(node1_tag);
    DigraphNode* node2_ptr = get_node(node2_tag);
    if (node1_ptr && node2_ptr) {
        for (DigraphEdge &e: *(node1_ptr->outedges)) {
            if (e.dest == node2_ptr) {
                edge = e;
                return true;
            }
        }
    }
    return false;
}

/**********************************************************/

bool Digraph::set_edge(string node1_tag, string node2_tag, float weight) {
    DigraphNode *node1_ptr = get_node(node1_tag);
    DigraphNode *node2_ptr = get_node(node2_tag);
    if (node1_ptr && node2_ptr) {
        for (DigraphEdge &e: *(node1_ptr->outedges)) {
            if (e.dest == node2_ptr) {
                e.weight = weight;
                break;
            }
        }

        for (DigraphEdge &e: *(node2_ptr->inedges)) {
            if (e.origin == node1_ptr) {
                e.weight = weight;
                break;
            }

        }
    } else {
        return false;
    }
    return true;
}

bool Digraph::get_route(Matrix<DijkstraAux> &Floyd, unordered_map<string, int> tag_to_index, vector<string> &path, string node1_tag, string node2_tag) { 
    path.clear();
    if (Floyd[tag_to_index[node1_tag]][tag_to_index[node2_tag]].predecessor) {
        int current = tag_to_index[node2_tag];
        path.push_back(node2_tag);
        while(current != tag_to_index[node1_tag]) {
            
            if (Floyd[tag_to_index[node1_tag]][current].predecessor) {

                string current_edge, current_node;
                current_edge = Floyd[tag_to_index[node1_tag]][current].edge_tag;
                current_node = Floyd[tag_to_index[node1_tag]][current].predecessor->tag;
                
                path.push_back(current_edge);
                path.push_back(current_node);
                
                current = tag_to_index[current_node];
            
            }
        }
        reverse(path.begin(), path.end());
        return true;
    } else {
        return false;
    }
}

bool Digraph::get_route(string node1_tag, string node2_tag, vector<string> &path) {
    path.clear();
    DigraphNode *current_node; 
    current_node = get_node(node2_tag);
    // Make sure the nodes are in the digraph
    if (get_node(node1_tag) && get_node(node2_tag)) {
        path.push_back(current_node->tag);
        DigraphEdge current_edge;
        while (current_node->tag != node1_tag) {
            DigraphNode *aux = ancestor(current_node);
            //get_edge(ancestor(current_node)->tag, current_node->tag, current_edge);
            if(ancestor(current_node) == nullptr || !get_edge(ancestor(current_node)->tag, current_node->tag, current_edge)) {
                path.clear();
                return false;
            }

            current_node = ancestor(current_node);

            if (!current_node) {
                path.clear();
                return false;
            }

            path.push_back(current_edge.tag);
            path.push_back(current_node->tag);
        }
        reverse(path.begin(), path.end());
        return true;
    } else {
        return false;
    }
    
}


 vector<string> Digraph::find_shortest_path(string node1_tag, string node2_tag, string algorithm) {
    vector<string> path;
    if (algorithm == "Dijkstra") {
        Digraph tree;
        vector<string> cycle;
        float cycle_len;
        bool found_path;
        found_path = dijkstra(node1_tag, tree, cycle, cycle_len);
        tree.get_route(node1_tag, node2_tag, path);
    } else if (algorithm == "Floyd") {
        Matrix<DijkstraAux> matrix(0, 0);
        vector<string> cycle;
        unordered_map<string, int> tag_to_index;
        float cycle_len;
        bool found_path;
        found_path = floyd(matrix, cycle, cycle_len, tag_to_index);
        get_route(matrix, tag_to_index, path, node1_tag, node2_tag);
    }
    
    return path;
}

