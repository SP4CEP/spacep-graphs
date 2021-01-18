/*
Filename: main.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 15/01/2021
Description: Main class of
*/
#include <iostream>
#include <fstream>
#include "linkedlist.h"
#include "graph.h"

using std::cout;
using std::endl;
using std::ifstream;

int main(){

    Graph G;

    ifstream file;
    
    std::string v="", v1, v2, tag;
    file.open("graph.txt");
    if(file.fail()){
        cout << "Error Opening File... \n";
        exit(1);
    }

    file >> v;
    while(v != "<TOKEN>"){
       G.add_node(v);
       file >> v;
    }
    while(file.eof() == false){
       file >> v1 >> v2 >> tag;
       G.add_edge(v1, v2, tag);
    }
    cout << "     **GRAPH**      " << endl;
    G.print();
    cout << "Nodes: " << G.node_count() << endl;
    cout << "Edges: " << G.edge_count() << endl;

    //G.remove_edges("d");
    //cout << "rm d: edge with a, c, f" << endl;
    //G.print();

    return 0;
}
