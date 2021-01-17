/*
Filename: linkedlist.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 17/01/2021
Description: Functions of the implementetion of a graph
*/
#include <iostream>
#include "graph.h"
#include "graphstructs.h"

//**********************************************************************//

bool Graph::add_node(string tag) {
    if (!find_node(tag)) { // If tag found
        GraphNode new_node;
        new_node.tag = tag;
        nodes.add(new_node);
        return true;
    }
    return false;
}

//**********************************************************************//

bool Graph::add_edge(string node1_tag, string node2_tag, string edge_tag) {
    //find both nodes
    GraphNode* p1 = get_node(node1_tag);
    GraphNode* p2 = get_node(node2_tag);
    if (!find_edge(edge_tag) && p1 && p2) {
        GraphEdge new_edge; // Link them using the graph edge as value
        new_edge.tag = edge_tag;
        new_edge.node = p2;
        p1->edges.add(new_edge);
        new_edge.node = p1;
        p2->edges.add(new_edge);
        return true;
    }
    return false;
}

//**********************************************************************//

bool Graph::remove_node(string tag) {
    GraphNode* p = get_node(tag);
    if (p) {
        GraphEdge tmp_edge; // pivot edge to delete edges
        for (GraphEdge edge: p->edges) {
            tmp_edge.tag = edge.tag; // assign the tag to delete from edges
            edge.node->edges.remove(tmp_edge);
        }
        nodes.remove(*p);
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
    for (GraphEdge edge: p1->edges) {
        if (edge.node == p2) {
            GraphEdge tmp_edge;
            tmp_edge.tag = edge.tag;
            p1->edges.remove(tmp_edge);
            p2->edges.remove(tmp_edge);
            found = true;
            break;
        }
    }
    return found;
}

//**********************************************************************//

bool Graph::remove_edge(string tag) {
    bool deleted = false;
    GraphEdge tmp_edge;
    tmp_edge.tag = tag;
    for (GraphNode node: nodes) {
        if (node.edges.remove(tmp_edge)) {
            deleted = true;
        }
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

    for (GraphEdge edge: node1_ptr->edges) {
        if (edge.node == node2_ptr) return true;
    }
    return false;
}

//**********************************************************************//

bool Graph::find_edge(string tag) {
    GraphEdge pivot_edge;
    pivot_edge.tag = tag;
    for (GraphNode node: nodes) {
        if (node.edges.find(pivot_edge)) return true;
    }
    return false;
}
