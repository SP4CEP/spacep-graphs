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
    N.add_node("b");
    N.add_node("c");
    N.add_node("d");
    N.add_node("e");
    N.add_node("f");
    N.add_node("g");
    N.add_node("h", 20, 7);
    N.add_node("i", 21, 9);
    N.add_node("j");
    N.add_node("k");
    N.add_node("l");
    N.add_node("m");
    N.add_node("n");


    N.add_edge("a", "b", "e1", 75, 2);
    N.add_edge("a", "d", "e2", 30);
    N.add_edge("a", "e", "e3", 33, 1);

    N.add_edge("b", "c", "e4", 46);
    N.add_edge("b", "e", "e5", 42);
    
    N.add_edge("c", "e", "e6", 29);
    N.add_edge("c", "f", "e7", 21, 3);
    
    N.add_edge("d", "e", "e8", 25);
    N.add_edge("d", "j", "e9", 15);
    N.add_edge("d", "h", "e10", 9);
    
    N.add_edge("e", "h", "e11", 12);
    
    N.add_edge("f", "e", "e12", 18);
    N.add_edge("f", "g", "e13", 8);
    N.add_edge("f", "i", "e14", 12);
    
    N.add_edge("g", "c", "e15", 40, 1);
    N.add_edge("g", "i", "e16", 40);
    
    N.add_edge("h", "f", "e17", 17);
    N.add_edge("h", "i", "e18", 10);
    N.add_edge("h", "k", "e19", 14, 2);
    
    N.add_edge("i", "k", "e20", 19);
    N.add_edge("i", "l", "e21", 25);
    
    N.add_edge("j", "h", "e22", 6);
    N.add_edge("j", "m", "e23", 45);
    
    N.add_edge("k", "j", "e24", 19, 1);
    N.add_edge("k", "l", "e25", 18);
    N.add_edge("k", "n", "e26", 50, 3);
    
    N.add_edge("l", "g", "e27", 70, 3);
    N.add_edge("l", "n", "e28", 62);
    
    N.add_edge("m", "k", "e29", 29);
    
    N.add_edge("n", "m", "e30", 54);


    N.set_source("a");
    N.set_source("b");
    N.set_source("c");

    N.set_terminus("k");
    N.set_terminus("m");
    N.set_terminus("n");

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
