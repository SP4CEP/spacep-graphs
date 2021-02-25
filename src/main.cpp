/*
Filename: main.cpp
Authors: Domínguez Acosta María Fernanda
         Murcia Yocupicio Raúl Octavio
         Sandoval del Hoyo María Ximena
Date: 15/01/2021
Description: Main file
*/
#include <iostream>
#include <fstream>
#include <vector>
#include "linkedlist.h"
#include "graph.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::vector;

void read_graph(string path, Graph &G) {
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

int main(int argc, char *argv[]) {
    string path;
    Graph G;

    if (argc < 2) {
        cout << "Missing graph source file" << endl;
        cout << "Using kruskal.txt" << endl;
        path = "examples/kruskal.txt";
    } else {
        path = argv[1];
    }

    cout << "Reading file " << path << endl;
    read_graph(path, G);

    G.print();

    //Graph forest = G.kruskal();


    return 0;
}
