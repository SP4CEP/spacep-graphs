#ifndef GRAPHRESULTS_H_INCLUDED
#define GRAPHRESULTS_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>

#include "digraph.h"
#include "network.h"
#include "graph.h"
#include "graphio.h"
#include "graphstructs.h"
#include "linkedlist.h"
#include "json.hpp"

using std::cout;
using std::string;
using std::ifstream;
using std::ofstream;
using std::setw;
using json = nlohmann::json;

//************************************************************************************************//
json result_false(string type){
    json j;
    j["res"] = false;
    return j;
}
//************************************************************************************************//
json partitions(LinkedList<string> P1, LinkedList<string> P2){
    json j;
    j["res"] = true;
    j["type"] = "partition";
    j["P1"] = json::array({});

    for(string &node: P1){
        j["P1"].push_back(node);
    }

    for(string &node: P2){
        j["P2"].push_back(node);
    
    }
    return j;
}

//************************************************************************************************//

void path(vector<string> path, json &j){
    //j["res"] = true;
    j["type"] = "path";
    j["path"] = json::array({});

    for (vector<string>::iterator it = path.begin() ; it != path.end(); ++it)
        j["path"].push_back(*it);
}

//************************************************************************************************//

json write_forest(vector<Graph> forest){
    json j, g;
    int fs = forest.size();
    float weight=0, w=0;
    if(fs > 1) j["res"] = true;
    else j["res"] = false;
    j["type"] = "forest";
    j["no_trees"] = fs;
    j["forest"] = json::array({});

    for(int i = 0; i < forest.size(); i++){
        g.clear();
        WriteGraph(forest[i], g);
        w = g["weight"];
        cout << g["weight"] << " aaaaaa " << w << endl;
        weight+=w;
        cout << "wrote graph..." << endl;
        cout << g << endl;
        j["forest"].push_back(g);
    }
    cout << "graqph weight " << w << endl;
    j["weight"] = weight;
    return j;
}

//************************************************************************************************//

json digraph_forest(vector<Digraph> forest, int index){
    json j, g;
    int fs = forest.size();
    if(fs > 1) j["res"] = true;
    else j["res"] = false;
    j["type"] = "short_paths";
    j["no_digs"] = fs;
    j["paths"] = json::array({});

    WriteDigraph(forest[index], g);
    j["paths"].push_back(g);
    return j;

}

//************************************************************************************************//
void write_cycle(vector<string> path, json &j){
    //j["res"] = true;
    j["type"] = "cycle";
    j["path"] = json::array({});
    vector<string>::iterator it = path.begin();
    //j["path"].push_back(*it);
    //cout << *it << endl;

    for (it = path.begin(); it != path.end()-1; it+=2){
        cout << *it << endl;
        j["path"].push_back(*it);
    }
    it = path.begin();
    j["path"].push_back(*it);
    cout << j << endl;
}

//************************************************************************************************//

#endif // GRAPHRESULTS_H_INCLUDED