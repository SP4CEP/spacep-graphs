#include <iostream>
#include <iomanip>
#include <fstream>

#include "digraph.h"
#include "network.h"
#include "graph.h"
#include "graphstructs.h"
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

        // READ NODES
        for (json::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            json node = *it;
            D.add_node(node["tag"]);
         }

        json edges = digraph["edges"];
        //READ EDGES
        for (json::iterator it = edges.begin(); it != edges.end(); ++it) {
            json edge = *it;
            D.add_edge(edge["src"], edge["dest"], edge["tag"], edge["weight"]);
         }

        D.print();

        return D;
}

//************************************************************************************************//

Graph ReadJsonGraph(json &graph){
        cout << "is graph" << endl;
        Graph G;
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
            G.add_edge(edge["src"], edge["dest"], edge["tag"], edge["weight"]);
         }

        G.print();
        return G; 
}

//************************************************************************************************//

Network ReadJsonNetwork(json &network){
        //cout << "is network" << endl;
        Network N;
        json nodes = network["nodes"];

        // READ NODES
        for (json::iterator it = nodes.begin(); it != nodes.end(); ++it) {
            json node = *it;
            
            if(node["capacity"].is_null() && node["restriction"].is_null())
                N.add_node(node["tag"]);
            
            else if(node["capacity"].is_number())
                N.add_node(node["tag"], node["capacity"]);
            else
               N.add_node(node["tag"], node["capacity"], node["restriction"]); 
            // set sources & terminuses
            if(node["type"] == "terminus") N.set_terminus(node["tag"]);
            if(node["type"] == "source") N.set_source(node["tag"]);
        }

        json edges = network["edges"];
        //READ EDGES
        for (json::iterator it = edges.begin(); it != edges.end(); ++it) {
            json edge = *it;
            if(edge["restriction"].is_null())
                N.add_edge(edge["src"], edge["dest"], edge["tag"], edge["capacity"]);
            else
                N.add_edge(edge["src"], edge["dest"], edge["tag"], edge["capacity"], edge["restriction"]);
         }

        N.print();
        return N;  
}

//************************************************************************************************//

void WriteDigraph(string filename, Digraph D){
    json write;
    //edges, nodes, type
    write["type"] = "digraph";
    write["nodes"] = json::array({});
    write["edges"] = json::array({});

    //WRITE NODE
    for(DigraphNode& node: D.get_nodes()){
        json n;
        n["tag"] = node.tag;
        write["nodes"].push_back(n);

        //WRITE EDGES
        for(DigraphEdge& edge: *(node.outedges)){
            json e;
            e["tag"] = edge.tag;
            e["origin"] = edge.origin->tag;
            e["dest"] = edge.dest->tag;
            e["weight"] = edge.weight;
            
            write["edges"].push_back(e);
        }
    }
    ofstream o(filename);
    o << setw(4) << write << endl;
}

void WriteGraph(string filename, Graph graph){
    //copy the graph to not modify original
    Graph G = graph;
    
    json write;
    //edges, nodes, type
    write["type"] = "graph";
    write["nodes"] = json::array({});
    write["edges"] = json::array({});

    string tag;

    //WRITE NODE
    for(GraphNode& node: G.get_nodes()){
        json n;
        n["tag"] = node.tag;
        write["nodes"].push_back(n);

        //WRITE EDGES
        for(GraphEdge& edge: *(node.edges)){
            json e;
            tag = edge.tag;
            e["origin"] = node.tag;
            e["dest"] = edge.node->tag;
            e["weight"] = edge.weight;
            write["edges"].push_back(e);

            //Remove it from copy so we don't write it twice
            G.remove_edge(tag);
        }
    }
    ofstream o(filename);
    o << setw(4) << write << endl; 
}

void WriteNetwork(string filename, Network N){
       //copy the graph to not modify original
    //Network  = N;
    
    json write;
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

        if(node.capacity != numeric_limits<float>::infinity())
            n["capacity"] = node.capacity;
        
        if(node.restriction)
            n["restriction"] = node.restriction;

        write["nodes"].push_back(n);

        //WRITE EDGES
        for(NetworkEdge& edge: *(node.outedges)){
            json e;
            tag = edge.tag;
            e["origin"] = edge.origin->tag;
            e["dest"] = edge.dest->tag;
            e["capacity"] = edge.capacity;

            if(edge.restriction)
                e["restriction"] = edge.restriction;
            if(edge.flow)
                e["flow"] = edge.flow;

            write["edges"].push_back(e);

        }
    }
    ofstream o(filename);
    o << setw(4) << write << endl;  
}

void read_digraph(string path, Digraph &G) {
    ifstream file;
    G.clear();
    std::string v="", v1, v2, tag;
    int type;
    file.open(path);
    if(file.fail()){
        cout << "Error Opening File... \n";
        exit(1);
    }
    file >> type;
    G.set_type(type);
    file >> v;
    while(v != "<TOKEN>"){
       G.add_node(v);
       file >> v;
    }
    if(type == 0){
       while(file.eof() == false){
       file >> v1 >> v2 >> tag;
       G.add_edge(v1, v2, tag);
       }
    }else{
       float w;
       while(file.eof() == false){
       file >> v1 >> v2 >> tag >> w;
       G.add_edge(v1, v2, tag, w);
       } 
    }
}