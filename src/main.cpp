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
}
