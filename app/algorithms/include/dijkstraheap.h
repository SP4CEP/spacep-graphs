#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

#include "graphstructs.h"

using std::make_heap;
using std::push_heap;
using std::string;
using std::vector;
using std::unordered_map;
using std::greater;

class DijkstraHeap {
    vector<DijkstraAux> container;
    unordered_map<string, DijkstraAux> queue_node;
    greater<DijkstraAux> comp;

public:

    DijkstraHeap(int alloc_size = 0) {
        container.reserve(alloc_size);
    }

    void push(DijkstraAux n) {
        container.push_back(n);
        push_heap(container.begin(), container.end(), comp);
        queue_node.insert({n.node->tag, n});
    }
    
    
    DijkstraAux pop() {
        DijkstraAux aux = container.front();
        pop_heap(container.begin(), container.end(), comp);
        container.pop_back();
        queue_node.erase(aux.node->tag);
        return aux;
    }
    
    DijkstraAux top() {
        return container.front();
    }

    void update_priority(DijkstraAux n) {
        for (int i = 0; i < container.size(); i++) {
            if (container[i].node->tag == n.node->tag) {
                container[i] = n;
                queue_node[n.node->tag] = n;
                while (i > 0 && container[i] < container[(i-1)/2]) {
                    DijkstraAux aux = container[i];
                    container[i] = container[(i-1)/2];
                    container[(i-1)/2] = aux;
                    i = (i-1)/2;
                }
                break;
            }
        }
    }

    float get_priority(string tag) {
        return queue_node[tag].accumulated_weight;
    }
    
    DijkstraAux get(string tag) {
        return queue_node[tag];
    }

    bool is_empty() {
        return container.empty();
    }
};


#endif