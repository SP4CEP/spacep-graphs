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
#include "graph_results.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using json = nlohmann::json;

void menu_graph(json &g, int algo, string out_file);
void menu_digraph(json &d, int algo, string out_file);
void menu_network(json &d, int algo, string out_file);

int main(int argc, char *argv[]){
    //  argv[1]:    <input_file.json>
    //  argv[2]:    <output_file.json>
    //  argv[3]:    <no. of algoritmo>

    if(argc < 5){
        cout << "Usage: ./bin <input_file.json> <output_file.json <no. algoritmo>" << endl << endl << "Algorithms:" <<endl;
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
    }

    string in_file = argv[1];
    string out_file = argv[3];
    int algorithm = (atoi)(argv[2]);

    ifstream i(in_file);
    //cout << "file opened" << endl;
    json j, out;
    i >> j;
    //cout << "json file read" << endl;
    string type = j["type"];

    if(type == "network"){
        //cout << "network" << endl;
        Network N = ReadJsonNetwork(j);
        json out;
        //WriteNetwork(N, out);
        dump_file(out, out_file);

    }else if(type == "digraph"){
        //cout << "digraph" << endl;
        Digraph D = ReadJsonDigraph(j);
        json out;
        //WriteDigraph(out_file, D, out);
        dump_file(out, out_file);

    }else if(type == "graph"){
        //cout << "graph" << endl;
        Graph G = ReadJsonGraph(j);
        json out;
        //WriteGraph(G, out);
        dump_file(out, out_file);
    
    }else{
        cout << "ERROR" << endl;
    }
    return 0;
}

void menu_graph(json &g, int algo, string out_file){
    Graph G = ReadJsonGraph(g);

    // 2. IS GRAPH BIPARTITE
    if(algo ==2){
        LinkedList<string> P1, P2; 
        bool res = G.is_bipartite(&P1,&P2);
        json write;
        if(res) write = partitions(P1,P2);
        else write = result_false("graph");
        dump_file(write, out_file);
    
    // 3. FLEURY ALGORITHM (EULER PATH)
    }else if(algo == 3){
        vector<string> p;
        json write;
        bool res = G.find_eulerian_path(&p);

        if(res){
          write["res"] = true;  
          path(p, write);
        }else{
            write["res"] = false;  
            write = result_false("graph");
        }
        dump_file(write, out_file);
    
    // 4. BFS FOREST 
    }else if(algo == 4){
        vector<Graph> forest = G.bfs();
        json write = write_forest(forest);
        dump_file(write, out_file);

    // 5. DFS FOREST
    }else if(algo == 5){
        vector<Graph> forest = G.dfs();
        json write = write_forest(forest);
        dump_file(write, out_file);

    // 6. KRUSKAL ALGORITHM (minimum spanning forest)
    }else if(algo == 6){
        Graph r;
        json write;
        write["res"] = G.kruskal(r);
        WriteGraph(r, write);
        dump_file(write, out_file);
    
    // 7. PRIM ALGORITHM (minimum spanning forest)
    }else if(algo == 7){
        vector<Graph> forest;
        G.prim(forest);
        json write = write_forest(forest);
        dump_file(write, out_file);

    }else{
        cout << "error" << endl;
    }
}

void menu_digraph(json &d, int algo, string out_file){
    Digraph D = ReadJsonDigraph(d);

    // 8. DIJKSTRA ALGORITHM (shortest path)
    if(algo == 8){
        //dijkstra(string initial_tag, Digraph &tree, vector<string> &cycle, float &cycle_len, string destination_tag = "", bool optimize = true);
        // initial_tag, destination_tag(optional)
        bool res;
        Digraph tree;
        float cycle_len = 0;
        vector<string> cycle;
        json write;

        if(d["destination_tag"].is_null())
            res = D.dijkstra(d["initial_tag"], tree, cycle, cycle_len);
        else
            res = D.dijkstra(d["initial_tag"], tree, cycle, cycle_len,d["destination_tag"]);
        
        if(res){
            write["res"] = true;
            WriteDigraph(tree, write);
            dump_file(write, out_file);
        }else{
            write["res"] = false;
            if(cycle_len){
                write["type"]="cycle";
                path(cycle, write);
            }else{
                write["type"] = "disconnected";
            }
        }
    // 8. FLOYD ALGORITHM (shortest path)
    }else if(algo == 9){
        json write;
        // TODO: flata una función Mat2Digraphs jeje 👀
        dump_file(write, out_file);
    }else{
        cout << "error" << endl;
    }
}


void menu_network(json &n, int algo, string out_file){
    Network N = ReadJsonNetwork(n);
    
    // 10: FORD-FULKERSON ALGORITHM
    if(algo == 10){
        bool res;
        float total_flow=0;
        json write;

        if(n["target_flow"].is_null())
            res = N.general_ford_fulkerson(total_flow);
        else
            res = N.general_ford_fulkerson(total_flow, n["target_flow"]);
        
        write["res"] = res;
        // solution found
        if(res){
            write["total_flow"] = total_flow;
            WriteNetwork(N, write);
        }
        dump_file(write, out_file);

    // 11: PRIMAL ALGORITHM
    }else if(algo == 11){
        bool res;
        json write;

        res = N.primal_minimum_cost_flow(n["target_flow"]);
        write["res"] = res;
        if(res){
            write["optimal_cost"] = N.current_cost();
            WriteNetwork(N, write);
        }
        dump_file(write, out_file);

    // 12: DUAL ALGORITHM
    }else if(algo == 12){
        bool res;
        json write;

        res = N.dual_minimum_cost_flow(n["target_flow"]);
        write["res"] = res;
        if(res){
            write["optimal_cost"] = N.current_cost();
            WriteNetwork(N, write);
        }
        dump_file(write, out_file);

    // 13: SIMPLEX ALGORITHM
    }else if(algo == 13){
        bool res;
        json write;

        res = N.simplex(n["target_flow"]);
        write["res"] = res;
        if(res){
            write["optimal_cost"] = N.current_cost();
            WriteNetwork(N, write);
        }
        dump_file(write, out_file);

    }else{
        cout << "ERROR" << endl;
    }
}