#include <iostream>
#include <fstream>

#include "graph.h"
#include "digraph.h"
#include "network.h"

using std::cout;
using std::string;
using std::ifstream;


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