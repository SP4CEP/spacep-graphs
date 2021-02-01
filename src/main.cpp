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
    file.open(path);
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
}

int main(int argc, char *argv[]) {
    string path;
    Graph G;

    if (argc < 2) {
        cout << "Missing graph source file" << endl;
        cout << "Using graph.txt" << endl;
        path = "graph.txt";
    } else {
        path = argv[1];
    }


    cout << "Reading file " << path << endl;
    read_graph(path, G);

    vector<string> p1; 
    
    cout << "     **GRAPH**      " << endl;
    G.print();
    bool is_bip = G.find_eulerian_path(&p1);
    cout << "Eulerian path: " << std::boolalpha << is_bip << endl;
    for (auto i: p1)
        std::cout << i << ' ';
    cout << endl;
    /*
    LinkedList<string> p1, p2;

    cout << "     **GRAPH**      " << endl;
    G.print();
    bool is_bip = G.is_bipartite(&p1, &p2);
    cout << "Is bipartite: " << std::boolalpha << is_bip << endl;

    cout << "Partition 1" << endl;
    p1.print();
    cout << "Partition 2" << endl;
    p2.print();


    
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
*/
    return 0;
}
