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
#include "digraph.h"
#include "graphstructs.h"
#include "matrix.h"

using std::cout;
using std::endl;
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

int main(int argc, char *argv[]) {
    string path;
    Digraph G;

    if (argc < 2) {
        cout << "Missing graph source file" << endl;
        cout << "Using kruskal.txt" << endl;
        path = "examples/grafica2.txt";
    } else {
        path = argv[1];
    }

    cout << "Reading file " << path << endl;
    read_digraph(path, G);
    G.print();
    vector<string> cycle;
    float len_cycle;

    Matrix<DijkstraAux> mat(1,1);

    cout << "Testing Floyd" << endl;

    if (G.floyd(mat, cycle, len_cycle)) {
        cout << "Solution found" << endl;
        G.printMatrix(mat);
    } else {
        cout << "Cycle of length " << len_cycle << " found" << endl;
        for (string tag: cycle)
            cout << tag << " ";
        cout << endl;
    }

    cout << "Testing Dijkstra" << endl;

    Digraph tree;

    if (G.dijkstra("a", tree, cycle, len_cycle)) {
        cout << "Solution found" <<  endl;
        tree.print();
    } else {
        cout << "Cycle of length " << len_cycle << " found" << endl;
        for (string tag : cycle)
            cout << tag << " ";
        cout << endl;
    }


    return 0;
}
