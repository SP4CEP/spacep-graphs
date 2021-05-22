#from app.gui.write import write_dict
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

#print(f'executing {bashCommand}')

#process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
#output, error = process.communicate()

#print(output)
#//print("\n\n\n")
#print(error)

# 4. Read 
#G = read.read_file(result, algorithm)

#write = write.write_dict(G)
#with open(outfile, 'w') as out:
#    json.dump(write, out)
        
#else:
#    print("ERROR")

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

    #read result
    #g_json = json.load(open(outfile))
    #print(g_json)
    gres = nx.MultiGraph()
    res, info, gres = read.read_graph(outfile,3)
    print("RESULTS")
    print(res)
    print(info)
    print(gres.nodes())
    print(gres.edges())
    return res, info, gres



# Write
#params = tuple()
#g = nx.MultiGraph()
#g.graph['type']='graph'
#g.add_node("a")
#g.add_node("b")
#g.add_node("c")
#g.add_node("d")
#g.add_edge("a","b", weight=4)
#g.add_edge("a","c", weight=3)
#g.add_edge("a","d", weight=1)
#graph_data = nx.node_link_data(g)
#print(g.nodes)
#print(g.edges)
#print("*")
#print("*")
#run_graph(g,7)

test = ""
if test is None:
    print("isnone")
else:
    print("smt else")

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

    if algorithm == 8 and params[1] != "":
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

    
    


g = nx.DiGraph()
g.add_node("a")
g.add_node("b")
g.add_node("c")
g.add_node("d")
g.add_edge("a", "c", weight=4)
g.add_edge("c", "b", weight=4)
g.add_edge("b", "d", weight=4)
g.add_edge("d", "e", weight=4)
g.add_edge("e", "a", weight=4)

l = ("a", "c")
#run_digraph(g,8,l)
params=("a", "")
infile = "files/digraph/input/g.json"
outfile = "files/digraph/output/g.json"

#print(g_json)

algorithm=8
bashCommand = f'{executable} {infile} {outfile} {algorithm}'
print(f'executing {bashCommand}')

process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, _ = process.communicate()
print(output)

#read result
g_json = json.load(open(outfile))
print("reading file from results")
print(g_json)
res, info, gres = read.read_digraph(outfile, algorithm, params)
#res, info, gres = read.read_digraph(outfile, algorithm, params)
#res, info, gres = run_digraph(g,8,l)
#print("RESULTS")
print(res)
print(info)
print(gres.nodes())
print(gres.edges())
    # Dijkstra
#    if algorithm == 8:

    
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
