#ifndef GRAPHIO_H_INCLUDED
#define GRAPHIO_H_INCLUDED


#include <iostream>
#include <iomanip>
#include <fstream>

#include "digraph.h"
#include "network.h"
#include "graph.h"
#include "graphstructs.h"
#include "linkedlist.h"
#include "json.hpp"

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::setw;
using json = nlohmann::json;

//************************************************************************************************//

Digraph ReadJsonDigraph(json &digraph){
        Digraph D;
        json nodes = digraph["nodes"];
        if(digraph["weighted"]) D.set_type(1);
        else D.set_type(0);

        // READ NODES
        for (json::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            json node = *it;
            D.add_node(node["tag"]);
        }

        json edges = digraph["edges"];
        //READ EDGES
        for (json::iterator it = edges.begin(); it != edges.end(); ++it) {
            json edge = *it;
            if(digraph["weighted"])
                D.add_edge(edge["src"], edge["dest"], edge["tag"], edge["weight"]);
            else
                D.add_edge(edge["src"], edge["dest"], edge["tag"]);
        }
        //D.print();
        return D;
}

//************************************************************************************************//

Graph ReadJsonGraph(json &graph){
        //cout << "is graph" << endl;
        Graph G;
        float weight = 0;
        if(graph["weighted"]) G.set_type(1);
        else G.set_type(0);

        json nodes = graph["nodes"];

        // READ NODES
        for (json::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            json node = *it;
            G.add_node(node["tag"]);
         }

        json edges = graph["edges"];
        //READ EDGES
        for (json::iterator it = edges.begin(); it != edges.end(); ++it) {
            json edge = *it;
            if(graph["weighted"])
                G.add_edge(edge["src"], edge["dest"], edge["tag"], edge["weight"]);
            else
                G.add_edge(edge["src"], edge["dest"], edge["tag"]);    
         }

        G.print();
        return G; 
}

//************************************************************************************************//

Network ReadJsonNetwork(json &network){
        //cout << "is network" << endl;
        Network N;
        float q = numeric_limits<float>::infinity(),r = 0,f = 0,c = 0;
        json nodes = network["nodes"];

        // READ NODES
        for (json::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            json node = *it;
            
            if (node["capacity"] == 999999999){
                N.add_node(node["tag"], q, node["restriction"], node["production"]);
            }else{
                N.add_node(node["tag"], node["capacity"], node["restriction"], node["production"]);
            }
            // set sources & terminuses
            if(node["type"] == "terminus") N.set_terminus(node["tag"]);
            if(node["type"] == "source") N.set_source(node["tag"]);
        }

        json edges = network["edges"];
        //READ EDGES
        for (json::iterator it = edges.begin(); it != edges.end(); ++it) {
            json edge = *it;
            q = numeric_limits<float>::infinity();
            r = 0;
            f = 0;
            c = 0;

            //capacity
            if(edge["capacity"] != 999999999) q = edge["capacity"];
            //restriction
            r = edge["restriction"];
            //flow
            f = edge["flow"];
            //cost
            c = edge["cost"];
            
            N.add_edge(edge["src"], edge["dest"], edge["tag"], q, r, f, c);
        }
        //N.print();
        return N;  
}

//************************************************************************************************//

void WriteDigraph(Digraph D, json &write){

    //edges, nodes, type
    write["type"] = "digraph";
    write["nodes"] = json::array({});
    write["edges"] = json::array({});

    //if(D.get_weight()){
        write["weighted"] = true;
        write["weight"] = D.get_weight();
    //}

    //WRITE NODE
    for(DigraphNode& node: D.get_nodes()){
        json n;
        n["tag"] = node.tag;
        write["nodes"].push_back(n);

        //WRITE EDGES
        for(DigraphEdge& edge: *(node.outedges)){
            json e;
            e["tag"] = edge.tag;
            e["src"] = edge.origin->tag;
            e["dest"] = edge.dest->tag;
            e["weight"] = edge.weight;
            
            write["edges"].push_back(e);
        }
    }
}

//************************************************************************************************//

void WriteGraph(Graph &graph, json &write){
    //copy the graph to not modify original
    Graph G = graph;
    string tag;
    bool weighted;

    cout << "about to write in a json...." << endl;

    G.print();
    //edges, nodes, type
    write["type"] = "graph";
    write["nodes"] = json::array({});
    write["edges"] = json::array({});

    //if(G.get_weight()){
        weighted = true;
        write["weighted"] = weighted;
        write["weight"] = G.get_weight();
    //}else{
    //    weighted = false;
//       write["weighted"] = weighted; 
  //  }

    //WRITE NODE
    for(GraphNode& node: G.get_nodes()){
        json n;
        n["tag"] = node.tag;
        write["nodes"].push_back(n);

        //WRITE EDGES
        for(GraphEdge& edge: *(node.edges)){
            json e;
            e["tag"] = edge.tag;
            e["src"] = node.tag;
            e["dest"] = edge.node->tag;
            //if(weighted) 
            e["weight"] = edge.weight;
            write["edges"].push_back(e);

            //Remove it from copy so we don't write it twice
            G.remove_edge(edge.tag);
        }
    }
}
//************************************************************************************************//

void WriteNetwork(Network Net, json &write){
    //copy the network to not modify original
    Network N = Net;
    
    //edges, nodes, type
    write["type"] = "network";
    write["nodes"] = json::array({});
    write["edges"] = json::array({});

    vector<string> sources = N.get_sources();
    vector<string> terminuses = N.get_terminuses();
    string tag;

    //WRITE NODE
    for(NetworkNode& node: N.get_nodes()){
        json n;
        n["tag"] = node.tag;
        
        // check if node is source
        vector<string>::iterator it_s = find(sources.begin(), sources.end(), node.tag);
        if (it_s != sources.end())
            n["type"] = "source";

        // check if node is terminus
        vector<string>::iterator it_t = find(terminuses.begin(), terminuses.end(), node.tag);
        if (it_t != terminuses.end())
            n["type"] = "terminus";

        if(node.capacity == numeric_limits<float>::infinity())
            n["capacity"] = 999999999;
        else
            n["capacity"] = node.capacity;
        
        n["restriction"] = node.restriction;
        n["production"] = node.production;

        write["nodes"].push_back(n);

        //WRITE EDGES
        for(NetworkEdge& edge: *(node.outedges)){
            json e;
            e["tag"] = edge.tag;
            e["src"] = edge.origin->tag;
            e["dest"] = edge.dest->tag;

            if(edge.capacity == numeric_limits<float>::infinity())
                e["capacity"] = 999999999;
            else
                e["capacity"] = edge.capacity;
            
            e["restriction"] = edge.restriction;
            e["flow"] = edge.flow;
            e["cost"] = edge.cost;

            write["edges"].push_back(e);

        }
    }
}

//************************************************************************************************//
void dump_file(json &write, string out_file){
    ofstream o(out_file);
    o << setw(4) << write << endl;
    cout << "file written" << endl;
}
#endif // GRAPHIO_H_INCLUDED