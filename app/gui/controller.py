#from app.gui.write import write_dict
#from app.gui.write import write_network
import subprocess
import networkx as nx
import json
import read
import write

path = "files/"
infile = path
outfile = path
executable = "./bin/all.out"


# 1. Get graph and write it
# 2. Networkx to json
# 3. Exec binary and algorithm
# 4. Read result graph and display

# 3. Exec algorithm
#
#   ALGORITHMS
#    GRAPH
#
#   1: Graph operations
#   2: Calculate if graph is bipartite & partitions
#   3: Calculate euler path (Fleury's Algorithm)
#   4: BFS expansion tree
#   5: DFS expansion tree
#   6: Kruskal minimun spanning forest
#   7: Prim minimum spanning tree
#   
#   DIGRAPH 
#
#   8: Shortest path (Dijkstra's algorithm)
#   9: Shortest paths (Floyd-Warshall Algorithm)
#   
#   NETWORK
#
#   10: Maximun flow in a network (Ford-Fulkerson Algorithm)
#   11: Primal algorithm
#   12: Dual algorithm
#   13: Simplex algorithm


def run_graph(g, algo):
    global infile
    global outfile

    infile = "files/graph/input/g.json"
    outfile = "files/graph/output/g.json"

    g.graph["weighted"] = True
    g.graph["type"] = "graph"
    #print(params)
    
    # All graph algorithms works same
    graph = write.write_dict(g)
    #print(graph)
    with open(infile, 'w') as out:
        json.dump(graph, out)

    bashCommand = f'{executable} {infile} {outfile} {algo}'
    print(f'executing {bashCommand}')

    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    output, _ = process.communicate()
    print(output)

    gres = nx.MultiGraph()
    res, info, gres = read.read_graph(outfile,algo)
    print("RESULTS")
    print(res)
    print(info)
    print(gres.nodes())
    print(gres.edges())
    return res, info, gres



def receive_graph(G):
    graph_data = nx.node_link_data(G)
    print(graph_data)

def run_digraph(d, algorithm, params):
    global infile
    global outfile

    infile = "files/digraph/input/g.json"
    outfile = "files/digraph/output/g.json"

    d.graph["weighted"] = True
    d.graph["type"] = "digraph"

    d_json = write.write_digraph(d)
    d_json["initial_tag"] = params[0]
    print("param etros")
    print(len(params))
    print(params)
    print(type(params))
    if algorithm == 8 and len(params) != 1:
        d_json["destination_tag"] = params[1]
    print(d_json)

    with open(infile, 'w') as out:
        json.dump(d_json, out)

    bashCommand = f'{executable} {infile} {outfile} {algorithm}'
    print(f'executing {bashCommand}')

    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    output, _ = process.communicate()
    print(output)

    #read result
    g_json = json.load(open(outfile))
    print(g_json)
    res, info, gres = read.read_digraph(outfile, algorithm, params)
    return res, info, gres

def run_network(n, algorithm, params):
    global infile
    global outfile

    infile = "files/network/input/g.json"
    outfile = "files/network/output/g.json"

    n.graph["weighted"] = True
    n.graph["type"]="network"

    net = write.write_network(n)
     
     #ford fulkerson
    if len(params) != 0:
        net["target_flow"] = params[0]
    
    print(net)

    with open(infile, 'w') as out:
        json.dump(net, out)

    bashCommand = f'{executable} {infile} {outfile} {algorithm}'
    print(f'executing {bashCommand}')

    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    output, _ = process.communicate()
    print(output)

    #read result
    g_json = json.load(open(outfile))
    print("results read")
    if len(params) != 0:
        g_json["target_flow"] = params[0]
    print(g_json)
    res, info, gres = read.read_network(g_json, algorithm, params)
    print("from controller got results")
    print(gres)
    print(res)
    print(info)
    return res, info, gres




    #return res
    


    
    #print(params)
    
    # All graph algorithms works same
#    graph = write.write_dict(g)
    #print(graph)
#    with open(infile, 'w') as out:
#        json.dump(graph, out)

#    bashCommand = f'{executable} {infile} {outfile} {algo}'
#    print(f'executing {bashCommand}')

#    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
#    output, _ = process.communicate()
#    print(output)

    #read result
    #g_json = json.load(open(outfile))
    #print(g_json)
#    gres = nx.MultiGraph()
#    return res, info, gres
