/*
filename: main.cpp
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
    //  argv[1]:    <input_file.json>
    //  argv[2]:    <output_file.json>
    //  argv[3]:    <no. of algoritmo>

    /*if(argc < 5){
        cout << "Usage: ./bin <input_file.json> <output_file.json <no. algoritmo>" << endl << "Algorithms:" <<endl;
        // GRAPH 
        cout << "1: Graph operations" << endl;
        cout << "2: Calculate if graph is bipartite & partitions" << endl;
        cout << "3: Calculate euler path (Fleury's Algorithm)" << endl;
        cout << "4: BFS expansion tree" << endl;
        cout << "5: DFS expansion tree" << endl;
        cout << "6: Kruskal minimun spanning forest" << endl;
        cout << "7: Prim minimum spanning tree" << endl;
        // DIGRAPH 
        cout << "8: Shortest path (Dijkstra's algorithm)" << endl;
        cout << "9: Shortest paths (Floyd-Warshall Algorithm)" << endl;
        // NETWORK
        cout << "10: Maximun flow in a network (Ford-Fulkerson Algorithm)" << endl;
        cout << "11: Primal algorithm" << endl;
        cout << "12: Dual algorithm" << endl;
        cout << "13: Simplex algorithm" << endl;
    }*/

    string in_file = argv[1];
    //string out_file = argv[3];
    int algorithm = (atoi)(argv[2]);

    ifstream i(in_file);
    cout << "file opened" << endl;
    json j, out;
    i >> j;
    cout << "json file read" << endl;
    string type = j["type"];

    if(type == "network"){
        cout << "network" << endl;
        Network N = ReadJsonNetwork(j);
        json out;
        WriteNetwork("examples/network/out_net.json", N, out);

    }else if(type == "digraph"){
        cout << "digraph" << endl;
        Digraph D = ReadJsonDigraph(j);
        json out;
        WriteDigraph("examples/digraph/out_dig.json", D, out);

    }else if(type == "graph"){
        cout << "graph" << endl;
        Graph G = ReadJsonGraph(j);
        json out;
        WriteGraph("examples/graph/out_gr.json", G, out);

    }else{
        cout << "ERROR" << endl;
    }
/*
    
    //              <<NETWORK ALGOS>>              //
    if (type == "network"){
        cout << "Reading network..." << endl;
        Network N = ReadJsonNetwork(j);

        switch (algorithm){
        
        case 10:
        //      **FORD-FULKERSON**      //
            cout << "Ford-Fulkerson algorithm" << endl;
            float total_flow;
            bool flow;
            //user set a target flow
            if(j["target_flow"].is_null()){
                flow = N.ford_fulkerson(total_flow);
            }else{
                float target_flow = j["target_flow"];
                flow = N.ford_fulkerson(total_flow, target_flow);
            }
            //output
            out["total_flow"] = total_flow;
            WriteNetwork(out_file, N, out);
            
            break;
        
        case 11: 
        //      **PRIMAL MINIMUM COST**     //
        
        case 12: 
        //      **DUAL MINIMUM COST**       //
        case 13:
       //           **SIMPLEX**             // 
        
        default:
            cout << "Algorithm not valid." << endl;
            break;
        }
    //            <<DIGRAPH ALGOS>>            //
    }else if(type == "digraph"){
        cout << "Reading digraph..." << endl;
        Digraph D = ReadJsonDigraph(j);

        switch (algorithm){
        //      **DIJKSTRA**        //
        case 8:
            Digraph tree;
            vector<string> cycle;
            float len_cycle;
            string initial_tag = j["initial_tag"];
            //optionals
            string destination_tag;
            bool optimize;

            if(j["destination_tag"].is_null()){
                
            }else{

            }
            break;
        //      **FLOYD**           //
        case 9:

            break;
        default:
            break;
        }


        
        WriteDigraph(out_file, D, out);

    }else if(type == "graph"){
        cout << "Reading graph..." << endl;
        Graph G = ReadJsonGraph(j);

        //      GRAPH ALGOS         //

        WriteGraph(out_file, G);

    }else{
        cout << "Enter a valid json file." << endl;
        return 1;
    }
*/
    return 0;
}
