#ifndef GRAPHSTRUCTS_H_INCLUDED
#define GRAPHSTRUCTS_H_INCLUDED

#include "linkedlist.h"

using std::string;
using std::ostream;

struct GraphEdge;
struct GraphNode;
struct AuxEdge;
struct DigraphEdge;
struct DigraphNode;
struct NetworkEdge;
struct NetworkNode;

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

struct DigraphEdge{
    string tag;
    DigraphNode* origin;
    DigraphNode* dest;
    float weight;
    bool operator==(const DigraphEdge &other) const {
        return tag == other.tag;
    };
    bool operator<(const DigraphEdge &other) const {
        return tag < other.tag;
    };
    bool operator>(const DigraphEdge &other) const {
        return tag > other.tag;
    };
    bool operator!=(const DigraphEdge &other) const {
        return !(*this == other);
    };
    bool operator<=(const DigraphEdge &other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const DigraphEdge &other) const {
        return *this > other || *this == other;
    };
};

inline ostream& operator<<(ostream& os, const DigraphEdge& edge) {
    return os << edge.tag;
}

struct DigraphNode {
    string tag;
    LinkedList<DigraphEdge>* inedges; 
    LinkedList<DigraphEdge>* outedges;
    bool operator==(const DigraphNode& other) const {
        return tag == other.tag;
    };
    bool operator<(const DigraphNode& other) const {
        return tag < other.tag;
    };
    bool operator>(const DigraphNode& other) const {
        return tag > other.tag;
    };
    bool operator!=(const DigraphNode &other) const {
        return !(*this == other);
    };
    bool operator<=(const DigraphNode &other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const DigraphNode &other) const {
        return *this > other || *this == other;
    };
};

inline ostream& operator<<(ostream& os, const DigraphNode& node) {
    return os << node.tag;
}

struct DijkstraAux {
    float accumulated_weight, edge_weight;
    DigraphNode *node, *predecessor;
    string edge_tag;

    void set(DigraphNode *n, DigraphNode *p, float ac, float w, string t="")
    {
        node = n;
        predecessor = p;
        edge_weight = w;
        accumulated_weight = ac;
    }

    void set(DigraphNode &n, DigraphNode &p, float ac, float w, string t){
        node = &n;
        predecessor = &p;
        edge_weight = w;
        accumulated_weight = ac;
        edge_tag = t;
    }
    bool operator==(const DijkstraAux& other) const {
        return accumulated_weight == other.accumulated_weight;
    };
    bool operator<(const DijkstraAux& other) const {
        return accumulated_weight < other.accumulated_weight;
    };
    bool operator>(const DijkstraAux& other) const {
        return accumulated_weight > other.accumulated_weight;
    };
    bool operator!=(const DijkstraAux& other) const {
        return !(*this == other);
    };
    bool operator<=(const DijkstraAux& other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const DijkstraAux& other) const {
        return *this > other || *this == other;
    };
};

inline ostream& operator<<(ostream& os, const DijkstraAux& a) {
    return os << a.predecessor->tag << ", " << a.accumulated_weight;
}

struct NetworkEdge{
    string tag;
    NetworkNode* origin;
    NetworkNode* dest;
    float capacity, restriction, flow, cost;

    bool operator==(const NetworkEdge &other) const {
        return tag == other.tag;
    };
    bool operator<(const NetworkEdge &other) const {
        return tag < other.tag;
    };
    bool operator>(const NetworkEdge &other) const {
        return tag > other.tag;
    };
    bool operator!=(const NetworkEdge &other) const {
        return !(*this == other);
    };
    bool operator<=(const NetworkEdge &other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const NetworkEdge &other) const {
        return *this > other || *this == other;
    };
};

inline ostream& operator<<(ostream& os, const NetworkEdge& edge) {
    return os << edge.tag;
}
struct NetworkNode {
    string tag;
    LinkedList<NetworkEdge>* inedges; 
    LinkedList<NetworkEdge>* outedges;
    float capacity, restriction;
    bool operator==(const NetworkNode& other) const {
        return tag == other.tag;
    };
    bool operator<(const NetworkNode& other) const {
        return tag < other.tag;
    };
    bool operator>(const NetworkNode& other) const {
        return tag > other.tag;
    };
    bool operator!=(const NetworkNode &other) const {
        return !(*this == other);
    };
    bool operator<=(const NetworkNode &other) const {
        return *this < other || *this == other;
    };
    bool operator>=(const NetworkNode &other) const {
        return *this > other || *this == other;
    };
};

inline ostream& operator<<(ostream& os, const NetworkNode& node) {
    return os << node.tag;
}

struct FordFulkersonTag {
    NetworkNode *predecessor;
    float flow;
    bool reverse;
    string edge_tag;
    
    FordFulkersonTag(){};

    FordFulkersonTag(NetworkNode *prev_node, float flow, bool reverse, string edge_tag) {
        this->predecessor = prev_node;
        this->flow = flow;
        this->reverse = reverse;
        this->edge_tag = edge_tag;
    };

    FordFulkersonTag &operator=(const FordFulkersonTag& other) {
        this->predecessor = other.predecessor;
        this->flow = other.flow;
        this->reverse = other.reverse;
        this->edge_tag = other.edge_tag;
        return *this;
    }
};

#endif
