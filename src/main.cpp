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
#include "network.h"
#include "graphstructs.h"
#include "matrix.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;


int main(int argc, char *argv[]) {
    Network N;

    N.add_node("a", 20, 10);
    N.add_node("b");

    N.add_edge("a", "b", "e1");
    N.print();

    N.clear();
    N.print();

    return 0;
}

/* 
void read_network(string path, Network &N) {
    ifstream file;
    N.clear();
    std::string v="", v1, v2, tag;
    int type;
    file.open(path);

    if(file.fail()){
        cout << "Error Opening File... \n";
        exit(1);
    }

    file >> type;
    
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
*/
