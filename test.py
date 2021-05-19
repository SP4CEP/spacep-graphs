import subprocess
import networkx as nx
import json

path = "app/files/digraph/"
filename = path + "graph8.json"
algorithm = 2
executable = "./bin/all.out"
result = 'files/digraph/graph8.json'
outfile = path + "dig_result.json"

bashCommand = f'{executable} {filename} {algorithm}'
print(f'executing {bashCommand}')

#process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
#output, error = process.communicate()

#print(output)

g = json.load(open(result))
#print(g)
G = nx.DiGraph()
G.graph["type"] = g["type"]
G.graph["weighted"] = g["weighted"]

for n in g["nodes"]:
    G.add_node(n["tag"])
for e in g["edges"]:
    if g["weighted"]:
        G.add_edge(e["src"], e["dest"], weight = e["weight"], tag = e["tag"])
        print("added edge")
    else:
        G.add_edge(e["src"], e["dest"], tag = e["tag"])

print(G.graph)
print("nodes: ", G.nodes(data=True))
print("edges: ", G.edges(data=True))