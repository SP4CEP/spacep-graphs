import subprocess
import networkx as nx
import json

path = "examples/network/"
filename = path + "network1011.json"
algorithm = 2
executable = "./all.out"
result = 'examples/network/out_net.json'
outfile = path + "net_result.json"

bashCommand = f'{executable} {filename} {algorithm}'
print(f'executing {bashCommand}')
# Exec algorithm
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()

print(output)
#//print("\n\n\n")
#print(error)

# Read 
g = json.load(open(result))

if g["type"] == "graph":
    G = nx.Graph()
    for n in g["nodes"]:
        G.add_node(n["tag"])
    for e in g["edges"]:
        if g["weighted"]:
            G.add_edge(e["origin"], e["dest"], weight = e["weight"], tag = e["tag"])
            print("added edge")
        else:
            G.add_edge(e["origin"], e["dest"], tag = e["tag"])

elif g["type"] == "digraph":
    D = nx.DiGraph()
    for n in g["nodes"]:
        D.add_node(n["tag"])
    for e in g["edges"]:
        if g["weighted"]:
            D.add_edge(e["origin"], e["dest"], weight = e["weight"], tag = e["tag"])
            print("added edge")
        else:
            D.add_edge(e["origin"], e["dest"], tag = e["tag"])

elif g["type"] == "network":
    print("im a net")
    D = nx.DiGraph()
    for n in g["nodes"]:
        q = float('inf')
        r = 0
        if "capacity" in n:
            q = n["capacity"]
        if "restriction" in n:
            r = n["restriction"]
        
        D.add_node(n["tag"], capacity=q, restriction=r)
    
    for e in g["edges"]:
        q = float('inf')
        r = 0
        f = 0
        c = 0
        if "capacity" in e:
            q = e["capacity"]
        if "restriction" in e:
            r = e["restriction"]
        if "flow" in e:
            f = e["flow"]
        if "cost" in e:
            c = e["cost"]
        
        D.add_edge(e["origin"], e["dest"], tag = e["tag"], capacity = q, restriction = r,
                    flow = f, cost = c)
        print("added edge")
    
    print(type(D.nodes(data=True)))
    print(type(D.edges(data=True)))
    print(D.number_of_edges())
    print("WRITE")
    
    nodes = []
    edges =[]


    for n in D.nodes(data=True):
        
        print(n)
        nodes.append({
            "tag": n[0],
            "restriction": n[1]['restriction'],
            "capacity": n[1]['capacity']
            })

    for e in D.edges(data=True):
        print(e)
        edge = {
            "tag": e[2]['tag'],
            "origin": e[0],
            "dest": e[1],
            "restriction": e[2]['restriction'],
            "flow": e[2]['flow'],
            "cost": e[2]['cost']
        }
        if e[2]['capacity']:
           edge["capacity"] = e[2]['capacity']
        
        edges.append(edge)


    write = {
        "type": "network",
        "nodes": nodes,
        "edges": edges
    }
    with open(outfile, 'w') as out:
        json.dump(write, out)
        
#    graph_data = nx.node_link_data(D)
#    print(graph_data)
else:
    print("ERROR")

# Write
