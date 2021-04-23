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

    N.add_node("a");
    N.add_node("b", 10, 5);
    N.add_node("c");
    N.add_node("d");
    N.add_node("e", 20, 10);
    N.add_node("f");
    N.add_node("g");
    N.add_node("h");
    N.add_node("i");
    N.add_node("j");

    N.add_edge("a", "b", "e1", 10);
    N.add_edge("a", "c", "e2", 5);
    N.add_edge("a", "d", "e3", 5);
    N.add_edge("a", "j", "e4", 20);
    N.add_edge("b", "c", "e5", 4);
    N.add_edge("b", "e", "e6", 10, 5);
    N.add_edge("c", "e", "e7", 9, 3);
    N.add_edge("c", "d", "e8", 8);
    N.add_edge("d", "e", "e9", 5);
    N.add_edge("e", "f", "e10", 20);
    N.add_edge("e", "g", "e11", 7);
    N.add_edge("f", "h", "e12", 9);
    N.add_edge("f", "i", "e13", 10);
    N.add_edge("g", "f", "e14", 10);
    N.add_edge("g", "i", "e15", 7);
    N.add_edge("i", "h", "e16", 20);
    N.add_edge("j", "d", "e17", 5);
    N.add_edge("j", "g", "e18", 10);

    N.set_source("a");
    N.set_source("j");

    N.set_terminus("h");
    N.set_terminus("i");

    N.print();

    float f;

    if (N.general_ford_fulkerson(f)) {
        cout << "Solution found! :)" << endl;
        N.print();
        cout << "Optimal flow : " << f << endl;
    } else {
        cout << "Solution not found :(((" << endl;
    }

    return 0;
}
