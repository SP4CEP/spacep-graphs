#ifndef GRAPHSTRUCTS_H_INCLUDED
#define GRAPHSTRUCTS_H_INCLUDED

#include "linkedlist.h"

using std::string;
using std::ostream;

struct GraphEdge;
struct GraphNode;
struct HeapEdge;

struct GraphEdge {
    string tag;
    GraphNode* node;
    float weight;
    bool operator==(const GraphEdge& other) const {
        return tag == other.tag;
    };
    bool operator<(const GraphEdge& other) const {
        return tag < other.tag;
    };
    bool operator>(const GraphEdge& other) const {
        return tag > other.tag;
    };
};

inline ostream& operator<<(ostream& os, const GraphEdge& edge) {
    return os << edge.tag;
}

struct GraphNode {
    string tag;
    LinkedList<GraphEdge> *edges;
    int partition_tag = 0;
    bool operator==(const GraphNode& other) const {
        return tag == other.tag;
    };
    bool operator<(const GraphNode& other) const {
        return tag < other.tag;
    };
    bool operator>(const GraphNode& other) const {
        return tag > other.tag;
    };
};

inline ostream& operator<<(ostream& os, const GraphNode& node) {
    return os << node.tag;
}

struct HeapEdge {
    string tag;
    GraphNode *node1, *node2;
    float weight;
    bool operator==(const HeapEdge& other) const {
        return weight == other.weight;
    };
    bool operator<(const HeapEdge& other) const {
        return weight < other.weight;
    };
    bool operator>(const HeapEdge& other) const {
        return weight > other.weight;
    };
};

#endif
