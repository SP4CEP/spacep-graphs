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
/*
    N.add_node("a");
    N.add_node("b");
    N.add_node("c");
    N.add_node("d");
    N.add_node("e");
    N.add_node("f");
    N.add_node("g");
    N.add_node("h");
    N.add_node("i");
    N.add_node("j");
    N.add_node("k");

    N.add_edge("a", "b", "e1", 19);
    N.add_edge("a", "c", "e2", 5);
    N.add_edge("a", "d", "e3", 74);
    N.add_edge("a", "f", "e4", 10);
    N.add_edge("b", "c", "e5", 1);
    N.add_edge("b", "g", "e6", 28);
    N.add_edge("c", "e", "e7", 10);
    N.add_edge("c", "f", "e8", 12);
    N.add_edge("d", "f", "e9", 2);
    N.add_edge("d", "i", "e10", 11);
    N.add_edge("e", "b", "e11", 6);
    N.add_edge("e", "f", "e12", 3);
    N.add_edge("e", "h", "e13", 8);
    N.add_edge("f", "h", "e14", 16);
    N.add_edge("f", "i", "e15", 18);
    N.add_edge("g", "e", "e16", 4);
    N.add_edge("g", "h", "e17", 6);
    N.add_edge("g", "j", "e18", 25);
    N.add_edge("h", "j", "e19", 46);
    N.add_edge("h", "k", "e20", 38);
    N.add_edge("i", "e", "e21", 15);
    N.add_edge("i", "h", "e22", 14);
    N.add_edge("i", "k", "e23", 12);
    N.add_edge("k", "j", "e24", 20);

    N.set_source("a");
    N.set_terminus("j");

    float flow;

    if (!N.ford_fulkerson(flow)) {
        cout << "Something missing... Hmmmm... 🤔" << endl;
    }

*/

    N.add_node("a");
    N.add_node("b");
    N.add_node("c");
    N.add_node("d");
    N.add_node("e");
    N.add_node("f");

    N.add_edge("a", "d", "e1", 7);
    N.add_edge("b", "d", "e2", 8);
    N.add_edge("c", "d", "e3", 2);
    N.add_edge("d", "e", "e4", 9);
    N.add_edge("d", "f", "e5", 10);

    N.set_source("a");
    N.set_source("b");
    N.set_source("c");

    N.set_terminus("e");
    N.set_terminus("f");

    N.print();

    float f;

    if (N.general_ford_fulkerson(f)) {
        cout << "Se encontró solución" << endl;
        N.print();
    } else {
        cout << "No se encontró solución :(((" << endl;
    }

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
