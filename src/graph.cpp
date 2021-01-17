#include "graph.h"

#include <iostream>

Graph::Graph() {
    ;
}

Graph::~Graph() {
    //to do
    ;
}

bool Graph::add_node(string tag) {
    if (!find_node(tag)) {
        GraphNode new_node;
        new_node.tag = tag;
        nodes.add(new_node);
        return true
    }
    return false
}

bool Graph::add_edge(string node1_tag, string node2_tag, string edge_tag) {
    GraphNode* p1 = find_node(node1_tag);
    GraphNode* p2 = find_node(node2_tag);
    if (!find_edge(edge_tag) && p1 && p2) {
        GraphEdge new_edge1;
        new_edge.tag = edge_tag;
        new_edge.node = p2;
        p1->edges.add(new_edge);
        new_edge.node = p1;
        p2->edges.add(new_edge);
        return true
    }
    return false
}

bool Graph::remove_node(string tag) {
    GraphNode* p = find_node(tag);
    for (GraphEdge edge: p->edges) {
        edge.node.edges.remove(*p)
    }
    nodes.remove(*p)
}

bool Graph::remove_edge(string node1_tag, string node2_tag) {
    GraphNode* p1 = find_node(node1_tag);
    GraphNode* p2 = find_node(node2_tag);
    p1->edges.remove(*p2)
    p2->edges.remove(*p1)
}

bool Graph::remove_edge(string tag) {
    GraphNode* p = find_node(tag);
    for (GraphNode node: nodes) {
        node.edges.remove(tag)
    }
}

bool Graph::find_node(string tag) {
    GraphNode temp_node;
    pivot_node.tag = tag;
    return (bool) nodes.find(temp_node);
}

GraphNode* Graph::find_node(string tag) {
    GraphNode temp_node;
    pivot_node.tag = tag
    auto list_node = nodes.find(temp_node);
    if (tmp) return &(tmp->value);
    return nullptr;
}

bool Graph::find_edge(string node1_tag, string node2_tag) {
    GraphNode* node1_ptr = find_node(node1_tag);
    GraphNode* node2_ptr = find_node(node2_tag);

    for (GraphEdge edge: node1_ptr->edges) {
        if (edge.node == node2_ptr) return true;
    }
    return false;
}

bool Graph::find_edge(string tag) {
    GraphEdge pivot_edge;
    pivot_edge.tag = tag;
    for (GraphNode node: nodes) {
        if (node.edges.find(pivot_edge)) return true
    }
    return false
}
