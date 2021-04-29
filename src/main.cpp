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
