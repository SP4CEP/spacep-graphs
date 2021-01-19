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

    //1)
    cout << "Nodes: " << G.node_count() << endl;
    cout << "Edges: " << G.edge_count() << endl;

    //2)
    cout << "Degree j: " << G.node_degree("j") << endl;
    cout << "Degree c: " << G.node_degree("c") << endl;
    cout << "Degree f: " << G.node_degree("f") << endl;

    //3)
    cout << "Find edge a b: " << G.find_edge("a", "b") << endl;
    cout << "Find edge c k: " << G.find_edge("c", "k") << endl;
    cout << "Find edge d f: " << G.find_edge("d", "f") << endl;

    //4)
    cout << "Delete f-h" << endl;
    G.remove_edge("f", "h");
    G.print();

    cout << "Delete g-j" << endl;
    G.remove_edge("g", "j");
    G.print();

    cout << "Delete a-e" << endl;
    G.remove_edge("a", "e");
    G.print();

    //5)
    cout << "Delete e" << endl;
    G.remove_node("e");
    G.print();

    ///6)
    cout << "Delete m" << endl;
    G.remove_node("m");
    G.print();

    ///7)
    cout << "Empty a" << endl;
    G.remove_edges("a");
    G.print();

    ///8)
    cout << "Degree d: " << G.node_degree("d") << endl;

    ///9)
    cout << "Copying G into H..." << endl;
    Graph H = G;
    cout << "Clearing G..." << endl;
    G.clear();

    cout << "Graph G" << endl;
    G.print();
    cout << "Graph H (G copy)" << endl;
    H.print();

    return 0;
}
