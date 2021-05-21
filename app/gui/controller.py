import subprocess
import networkx as nx
import json
import read
import write

path = "../../files/digraph/"
filename = path + "graph8.json"
algorithm = 2
executable = "./../../bin/all.out"
result = '../../files/digraph/graph8.json'
outfile = path + "dig_result.json"

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

#bashCommand = f'{executable} {filename} {algorithm}'
#print(f'executing {bashCommand}')

#process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
#output, error = process.communicate()

#print(output)
#//print("\n\n\n")
#print(error)

# 4. Read 
G = read.read_file(result, algorithm)

write = write.write_dict(G)
with open(outfile, 'w') as out:
    json.dump(write, out)
        
#    graph_data = nx.node_link_data(D)
#    print(graph_data)
#else:
#    print("ERROR")

# Write
