/*
Filename: main.cpp
Authors: Domínguez Acosta María Fernanda
         Sandoval del Hoyo María Ximena
         Murcia Yocupicio Raúl Octavio
Date: 15/01/2021
Description: Main file
*/

#include <iostream>
#include <fstream>
#include "digraph.h"
#include "network.h"
#include "graph.h"
#include "graphstructs.h"
#include "matrix.h"
#include "json.hpp"
#include "graphio.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using json = nlohmann::json;

int main(int argc, char *argv[]){
    /*
    Network N;

    N.add_node("a");
    N.add_node("b");
    N.add_node("c");
    N.add_node("d");
    N.add_node("e");
    N.add_node("f");
    N.add_node("g");


    N.add_edge("a", "b", "e1", 5, 0, 0, 5);
    N.add_edge("a", "c", "e2", 20, 0, 0, 4);
    N.add_edge("a", "d", "e3", 15, 3, 0, 3);

    N.add_edge("b", "f", "e4", 18, 0, 0, -2);

    N.add_edge("c", "d", "e5", 30, 5, 0, -7);
    N.add_edge("c", "g", "e6", 40, 4, 0, 8);
    
    N.add_edge("d", "e", "e7", 20, 10, 0, 0);

    N.add_edge("e", "f", "e8", 25, 0, 0, 5);

    N.add_edge("g", "f", "e9", 10, 0, 0, 3);

    N.set_source("a");

    N.set_terminus("f");

    N.print();

    //float f;

    if (N.primal_minimum_cost_flow(14)) {
        cout << "Solution found! :)" << endl;
        N.print();
        cout << "Optimal cost : " << N.current_cost() << endl;
    } else {
        cout << "Solution not found :(((" << endl;
    }

    return 0;

    */

    Digraph D;

    D.add_node("a");
    D.add_node("b");
    D.add_node("c");
    D.add_node("d");
    D.add_node("e");
    D.add_node("f");
    D.add_node("g");

    D.add_edge("a", "b", "e1", 15);
    D.add_edge("a", "c", "e2", 9);
    D.add_edge("a", "d", "e3", 7);
    D.add_edge("b", "c", "e4", -3);
    D.add_edge("b", "e", "e5", 7);
    D.add_edge("c", "a", "e6", -9);
    D.add_edge("c", "b", "e7", 3);
    D.add_edge("c", "d", "e8", 8);
    D.add_edge("c", "e", "e9", 20);
    D.add_edge("d", "a", "e10", -7);
    D.add_edge("d", "f", "e11", 3);
    D.add_edge("e", "b", "e12", -7);
    D.add_edge("e", "c", "e13", 2);
    D.add_edge("e", "g", "e14", 20);
    D.add_edge("f", "d", "e15", -3);
    D.add_edge("f", "e", "e21", 7);
    D.add_edge("f", "g", "e17", 13);
    D.add_edge("g", "e", "e18", -20);
    D.add_edge("g", "f", "e19", -13);

    D.print();

    Digraph T;
    vector<string> cycle;
    float cycle_len;

    if (D.dijkstra("a", T, cycle, cycle_len)) {
        cout << "Se encontró solución";
        T.print();
    } else {
        cout << "Se encontró un ciclo de longitud: " << cycle_len << endl;
        for (string n : cycle)
            cout << n << " ";
        cout << endl;
        
    }

    /*
    string filename = "digrafasdf.json";
    ifstream i("examples/digraph.json");
    json j;
    i >> j;
    string type = j["type"];
    
    if (type == "network"){
        cout << "Reading network..." << endl;
        Network N = ReadJsonNetwork(j);

        //      NETWORK ALGOS       //

        WriteNetwork(filename, N);
        cout << "file written" << endl;

    }else if(type == "digraph"){
        cout << "Reading digraph..." << endl;
        Digraph D = ReadJsonDigraph(j);
        
        //      DIGRAPH ALGOS       //
        
        WriteDigraph(filename, D);

    }else if(type == "graph"){
        cout << "Reading graph..." << endl;
        Graph G = ReadJsonGraph(j);

        //      GRAPH ALGOS         //

        WriteGraph(filename, G);

    }else{
        cout << "Enter a valid json file." << endl;
        return 1;
    }

    return 0;
    */
}
