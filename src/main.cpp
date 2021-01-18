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

int main(){
    // creation ***********************************
    cout << "creando G" << endl;
    Graph G;
    cout << "G creado" << endl;
    G.print();

    // add vertices ***********************************
    G.add_node("v1");
    cout << "v1 creado" << endl;
    G.print();

    G.add_node("v2");
    cout << "v2 creado" << endl;
    G.print();

    G.add_node("v3");
    cout << "v3 creado" << endl;
    G.print();

    G.add_node("v4");
    cout << "v4 creado" << endl;
    G.print();

    // add edges ***********************************
    G.add_edge("v1", "v2", "e1");
    cout << "v12 creado" << endl;
    G.print();

    G.add_edge("v2", "v3", "e2");
    cout << "v23 creado" << endl;
    G.print();

    G.add_edge("v3", "v4", "e3");
    cout << "v34 creado" << endl;
    G.print();

    // delete edges ******************************
    G.remove_edge("e3");
    cout << "e3 eliminado" << endl;
    G.print();

    G.remove_edge("v1", "v2");
    cout << "v1 v2 eliminado" << endl;
    G.print();

    //delete nodes *******************
    G.remove_node("v3");
    cout << "v3 eliminado" << endl;
    G.print();
    return 0;
}
