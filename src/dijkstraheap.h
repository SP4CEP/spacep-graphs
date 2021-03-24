#ifndef GRAPHSTRUCTS_H_INCLUDED
#define GRAPHSTRUCTS_H_INCLUDED

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

    DijkstraHeap::DijkstraHeap(int alloc_size = 0) {
        container.reserve(alloc_size);
    }

    void DijkstraHeap::push(DijkstraAux n) {
        container.push_back(n);
        push_heap(container.begin(), container.end(), comp);
        queue_node.insert({n.node->tag, n});
    }
    
    
    DijkstraAux DijkstraHeap::pop() {
        DijkstraAux aux = container.front();
        pop_heap(container.begin(), container.end(), comp);
        container.pop_back();
        queue_node.erase(aux.node->tag);
        return aux;
    }
    
    DijkstraAux DijkstraHeap::top() {
        return container.front();
    }

    void DijkstraHeap::update_priority(DijkstraAux n) {
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

    float DijkstraHeap::get_priority(string tag) {
        return queue_node[tag].weight;
    }
    
    DijkstraAux DijkstraHeap::get(string tag) {
        return queue_node[tag];
    }
};


#endif