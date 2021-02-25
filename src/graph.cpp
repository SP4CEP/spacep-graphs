/*
Filename: linkedlist.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 17/01/2021
Description: Functions of the implementetion of a graph
*/
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include "graphstructs.h"
#include "linkedlist.h"
#include "graph.h"

using std::cout;
using std::endl;
using std::string;
using std::unordered_set;
using std::unordered_map;
using std::queue;
using std::priority_queue;
using std::stack;
using std::greater;

Graph::Graph() : num_edges(0), num_nodes(0) {}

//**********************************************************************//

Graph::Graph(const Graph &G) : num_edges(0), num_nodes(0) {
    *this = G;
}

//**********************************************************************//

Graph& Graph::operator=(const Graph &G) {
    if (this == &G) return *this;
    // set to keep already added nodes
    unordered_set<string> added_edges;
    clear();
    // add each node
    for (ListNode<GraphNode> *p=G.nodes.start; p; p=p->next) {
        add_node((p->value).tag);
    }
    // iterate edges for each node
    for (ListNode<GraphNode> *p=G.nodes.start; p; p=p->next) {
        for (ListNode<GraphEdge> *q=(p->value).edges->start; q; q=q->next) {
            if (added_edges.find((q->value).tag) == added_edges.end()) {
                // if tag not already added
                add_edge((p->value).tag, (q->value).node->tag, (q->value).tag);
                added_edges.insert((q->value).tag);
            }
        }
    }
    return *this;
}

//**********************************************************************//

Graph::~Graph() {
    clear();
}

//**********************************************************************//

bool Graph::add_node(string tag) {
    if (!find_node(tag)) { // If tag found
        GraphNode new_node = {
            .tag = tag,
            .edges = new LinkedList<GraphEdge>,
            .partition_tag = 0
        };
        nodes.add(new_node);
        num_nodes++;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Graph::add_edge(string node1_tag, string node2_tag, string edge_tag, float weight) {
    //find both nodes
    GraphNode* p1 = get_node(node1_tag);
    GraphNode* p2 = get_node(node2_tag);
    if (!find_edge(edge_tag) && p1 && p2) {
        GraphEdge new_edge = { // Link them using the graph edge as value
            .tag = edge_tag,
            .node = p2,
            .weight = weight
        };
        p1->edges->add(new_edge);
        new_edge.node = p1;
        p2->edges->add(new_edge);
        num_edges++;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Graph::remove_node(string tag) {
    GraphNode* p = get_node(tag);
    if (p) {
        GraphEdge tmp_edge; // pivot edge to delete edges
        for (GraphEdge& edge: *(p->edges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.node->edges->remove(tmp_edge);
        }
        delete p->edges;
        nodes.remove(*p);
        num_nodes--;
        return true;
    }
    return false;
}

//**********************************************************************//

bool Graph::remove_edge(string node1_tag, string node2_tag) {
    GraphNode* p1 = get_node(node1_tag);
    GraphNode* p2 = get_node(node2_tag);
    if (!p1 || !p2) return false;
    bool found = false;
    for (GraphEdge& edge: *(p1->edges)) {
        if (edge.node == p2) {
            GraphEdge tmp_edge;
            tmp_edge.tag = edge.tag;
            p1->edges->remove(tmp_edge);
            p2->edges->remove(tmp_edge);
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

bool Graph::remove_edge(string tag) {
    bool deleted = false;
    GraphEdge tmp_edge;
    tmp_edge.tag = tag;
    for (GraphNode& node: nodes) {
        if (node.edges->remove(tmp_edge)) {
            if (deleted) break; // both edges in both nodes already deleted
            else if (node.edges->remove(tmp_edge)) {
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

bool Graph::find_node(string tag) {
    return (bool) get_node(tag);
}

//**********************************************************************//

GraphNode* Graph::get_node(string tag) {
    GraphNode temp_node;
    temp_node.tag = tag;
    auto list_node = nodes.find(temp_node);
    if (list_node) return &(list_node->value);
    return nullptr;
}

//**********************************************************************//

bool Graph::find_edge(string node1_tag, string node2_tag) {
    GraphNode* node1_ptr = get_node(node1_tag);
    GraphNode* node2_ptr = get_node(node2_tag);
    if (node1_ptr && node2_ptr) {
        for (GraphEdge& edge: *(node1_ptr->edges)) {
            if (edge.node == node2_ptr) return true;
        }
    }
    return false;
}

//**********************************************************************//

bool Graph::find_edge(string tag) {
    GraphEdge tmp_edge;
    tmp_edge.tag = tag;
    for (GraphNode& node: nodes) {
        if (node.edges->find(tmp_edge)) return true;
    }
    return false;
}

//**********************************************************************//

int Graph::node_degree(string tag) {
    GraphNode* temp_node = get_node(tag);
    LinkedList<GraphEdge> *edge_list = temp_node->edges;

    return (*edge_list).Length();
}

//**********************************************************************//

int Graph::node_degree(GraphNode node) {
    return node.edges->Length();
}

//**********************************************************************//

int Graph::node_count() {
    return nodes.Length();
}

//**********************************************************************//

int Graph::edge_count() {
    int total = 0;
    for (GraphNode node: nodes) {
        total += node.edges->Length();
    }
    return total / 2;
}

//**********************************************************************//

bool Graph::remove_edges(string tag) {
    GraphNode* p = get_node(tag);
    if (p) {
        GraphEdge tmp_edge; // pivot edge to delete edges
        for (GraphEdge& edge: *(p->edges)) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.node->edges->remove(tmp_edge);
        }
        p->edges->clear();
        return true;
    }
    return false;
}

//**********************************************************************//

void Graph::clear() {
    for (GraphNode node: nodes) {
        delete node.edges;
    }
    nodes.clear();
}

//**********************************************************************//

void Graph::print() {
    for (GraphNode& node: nodes) {
        cout << node;
        for (GraphEdge& edge: *(node.edges)) {
            cout << " | " << edge << " " << *(edge.node) ;
        }
        cout << endl;
    }
}

//**********************************************************************//

bool Graph::is_bipartite(LinkedList<string> *P1, LinkedList<string> *P2) {
    LinkedList<GraphNode*> frontier;
    GraphNode *p;
    bool found_partition = true;

    for (GraphNode& n : nodes) { // While nodes without tag exist
        if (n.partition_tag == 0) {
            n.partition_tag = 1;
            frontier.add(&n);
        }
        // for every node in the frontier
        while(frontier.Length() > 0 && found_partition) {
            frontier.pop_front(p);
            for (GraphEdge& e : *(p->edges)) {
                if (e.node->partition_tag == 0) { // not assigned tag yet
                    e.node->partition_tag = (p->partition_tag == 1 ? 2 : 1);
                    frontier.add(e.node);
                } else if (e.node->partition_tag == p->partition_tag) {
                    found_partition = false;
                    break;
                }
            }
        }
        if (!found_partition) break;
    }

    if (found_partition && P1 && P2) {
        P1->clear();
        P2->clear();
        for (GraphNode& n : nodes) {
            (n.partition_tag == 1 ? P1 : P2)->add(n.tag);
            n.partition_tag = 0;
        }
    } else {
        for (GraphNode& n : nodes)
            n.partition_tag = 0;
    }

    return found_partition;
}

//**********************************************************************//

bool Graph::find_eulerian_path(vector<string> *P) {
    string odd_nodes[2];
    int n_odd = 0;

    for (GraphNode& node : nodes) {
        if (node_degree(node) % 2 == 1) {
            if (n_odd == 2)
                return false;
            odd_nodes[n_odd] = node.tag;
            n_odd++;
        }
    }

    Graph G = *this;
    GraphNode* p = nullptr;
    queue<GraphNode*> q;
    stack<GraphNode*> s;
    unordered_set<string> visited;

    if (n_odd == 2) {
        // two nodes odd
        q.push(G.get_node(odd_nodes[0]));
        s.push(G.get_node(odd_nodes[1]));
        visited.insert(odd_nodes[0]);
        visited.insert(odd_nodes[1]);
    } else {
        // all nodes even
        q.push(&(G.nodes.start->value));
        s.push(&(G.nodes.start->value));
        visited.insert((G.nodes.start->value).tag);
    }

    while (G.node_degree(*q.back()) > 0 && G.node_degree(*s.top()) > 0) {
        p = q.back(); // vc
        if (G.node_degree(*p) > 0) {
            GraphNode* w = nullptr;
            for (GraphEdge& edge : *(p->edges)) {
                if (G.node_degree(*edge.node) > 1) {
                    w = edge.node;
                    break;
                }
            }
            if (w) {
                G.remove_edge(p->tag, w->tag);
                q.push(w);
                visited.insert(w->tag);
            }
        }
        p = s.top(); //vp
        if (G.node_degree(*p) == 1) {
            GraphNode *k = nullptr;
            k = (p->edges->start->value).node;
            G.remove_edge(p->tag, k->tag);
            s.push(k);
            visited.insert(k->tag);
        }
    }

    if (visited.size() < num_nodes) //graph is not connected
        return false;

    if (P) {
        P->clear();
        while (!q.empty()) {
            P->push_back(q.front()->tag);
            q.pop();
        }
        s.pop();
        while (!s.empty()) {
            P->push_back(s.top()->tag);
            s.pop();
        }
    }
    return true;
}

//***************************************************************//

vector<Graph> Graph::bfs() {
    GraphNode *t;
    queue<GraphNode*> q;
    unordered_map<string, bool> node_tags;
    int marked_nodes = 0;
    vector<Graph> forest;

    // initialize with false vaules
    for (GraphNode& node : nodes)
        node_tags.insert({node.tag, false});

    for (GraphNode& node : nodes) {
        if (node_tags[node.tag]) continue; // find unmarked node

        Graph tree;
        q.push(&node);
        node_tags[node.tag] = true; // mark node
        tree.add_node(node.tag);
        marked_nodes++;

        while (!q.empty()) {
            t = q.front(); // pop node out of queue
            q.pop();
            for (GraphEdge& edge : *(t->edges)) {
                if (!node_tags[edge.node->tag]) { // if neighbor unmarked
                    q.push(edge.node);
                    node_tags[edge.node->tag] = true; // mark node
                    tree.add_node(edge.node->tag);
                    tree.add_edge(t->tag, edge.node->tag, edge.tag);
                    marked_nodes++;
                }
            }
        }
        forest.push_back(tree);
        if (marked_nodes == num_nodes) break;
    }

    return forest;
}

//***************************************************************//

vector<Graph> Graph::dfs() {
    GraphNode *t;
    stack<GraphNode*> s;
    unordered_map<string, bool> node_tags;
    int marked_nodes = 0;
    vector<Graph> forest;

    // initialize with false vaules
    for (GraphNode& node : nodes)
        node_tags.insert({node.tag, false});

    for (GraphNode& node : nodes) {
        if (node_tags[node.tag]) continue; // find unmarked node

        Graph tree;
        s.push(&node);
        node_tags[node.tag] = true; // mark node
        tree.add_node(node.tag);
        marked_nodes++;

        while (!s.empty()) {
            t = s.top(); // get node on top of stack
            bool found_next = false; // flag to check if one available edge found
            for (GraphEdge& edge : *(t->edges)) {
                if (!node_tags[edge.node->tag]) {
                    found_next = true;
                    s.push(edge.node);
                    node_tags[edge.node->tag] = true; // mark node
                    tree.add_node(edge.node->tag);
                    tree.add_edge(t->tag, edge.node->tag, edge.tag);
                    marked_nodes++;
                    break; // breaks to continue on last added node
                }
            }
            if (!found_next) s.pop();
        }
        forest.push_back(tree);
        if (marked_nodes == num_nodes) break;
    }

    return forest;
}

string Graph::find_root(string node, unordered_map<string, string> &parent) {
    if(parent[node] == node) return node;
    parent[node] = find_root(parent[node], parent);
    return parent[node];
}

void Graph::union_root(string node1, string node2, unordered_map<string, string> &parent) {
    parent[find_root(node1, parent)] = find_root(node2, parent);
}

Graph Graph::kruskal() {
    priority_queue<HeapEdge, vector<HeapEdge>, greater<HeapEdge>> h;
    unordered_set<string> added_edges;
    unordered_map<string, string> parent;
    Graph expansion_tree;
    int tree_edges = 0;

    for (GraphNode node : nodes) {
        // add to expansion_tree
        expansion_tree.add_node(node.tag);
        // parents for union-find set
        parent.insert({node.tag, node.tag});
        // add each edge to the heap
        for (GraphEdge edge : *(node.edges)) {
            if (added_edges.find(edge.tag) == added_edges.end()) {
                HeapEdge e = {
                    .tag = edge.tag,
                    .node1 = &node,
                    .node2 = edge.node,
                    .weight = edge.weight
                };
                added_edges.insert(edge.tag);
                h.push(e);
            }
        }
    }

    while (tree_edges < num_nodes - 1) {
        if (h.empty()) break;
        HeapEdge edge = h.top();
        if (find_root(edge.node1->tag, parent) != find_root(edge.node2->tag, parent)) {
            expansion_tree.add_edge(edge.node1->tag, edge.node2->tag, edge.tag, edge.weight);
            union_root(edge.node1->tag, edge.node2->tag);
            ++tree_edges;
        }
        h.pop();
    }

    return expansion_tree;
}