#ifndef GRAPHSTRUCTS_H_INCLUDED
#define GRAPHSTRUCTS_H_INCLUDED

//#include <ostream>

using std::string;
using std::ostream;

struct GraphEdge;
struct GraphNode;

struct GraphEdge {
    string tag;
    GraphNode* node;
    bool operator==(const GraphEdge& other) {
        return tag == other.tag;
    };
    bool operator<(const GraphEdge& other) {
        return tag < other.tag;
    };
    bool operator>(const GraphEdge& other) {
        return tag > other.tag;
    };
};

inline ostream& operator<<(ostream& os, const GraphEdge& edge) {
    return os << edge.tag;
}

struct GraphNode {
    string tag;
    LinkedList<GraphEdge> *edges;
    bool operator==(const GraphNode& other) {
        return tag == other.tag;
    }
    bool operator<(const GraphNode& other) {
        return tag < other.tag;
    };
    bool operator>(const GraphNode& other) {
        return tag > other.tag;
    };
};

inline ostream& operator<<(ostream& os, const GraphNode& node) {
    return os << node.tag;
}

#endif
