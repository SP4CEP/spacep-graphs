#ifndef GRAPHSTRUCTS_H_INCLUDED
#define GRAPHSTRUCTS_H_INCLUDED

#include "linkedlist.h"

using std::string;
using std::ostream;

struct GraphEdge;
struct GraphNode;
struct AuxEdge;

struct GraphEdge {
    string tag;
    GraphNode* node;
    float weight;
    bool operator==(const GraphEdge &other) const {
        return tag == other.tag;
    };
    bool operator<(const GraphEdge &other) const {
        return tag < other.tag;
    };
    bool operator>(const GraphEdge &other) const {
        return tag > other.tag;
    };
    bool operator!=(const GraphEdge &other) const {
        return !(*this == other);
    };
    bool operator<=(const GraphEdge &other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const GraphEdge &other) const {
        return *this > other || *this == other;
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
    bool operator!=(const GraphNode &other) const {
        return !(*this == other);
    };
    bool operator<=(const GraphNode &other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const GraphNode &other) const {
        return *this > other || *this == other;
    };
};

inline ostream& operator<<(ostream& os, const GraphNode& node) {
    return os << node.tag;
}

struct AuxEdge {
    string tag;
    GraphNode *node1, *node2;
    float weight;
    AuxEdge(){};
    void set(GraphNode &n, GraphEdge &e) {
        tag = e.tag;
        node1 = &n;
        node2 = e.node;
        weight = e.weight;
    };
    bool operator==(const AuxEdge& other) const {
        return weight == other.weight;
    };
    bool operator<(const AuxEdge& other) const {
        return weight < other.weight;
    };
    bool operator>(const AuxEdge& other) const {
        return weight > other.weight;
    };
    bool operator!=(const AuxEdge& other) const {
        return !(*this == other);
    };
    bool operator<=(const AuxEdge& other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const AuxEdge& other) const {
        return *this > other || *this == other;
    };
    /* Añadir el resto de comparadores */
};

#endif
