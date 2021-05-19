import json
import networkx as nx

def read_graph(g):
    G = nx.Graph()
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
    
    print(type(G.nodes(data=True)))
    print(type(G.edges(data=True)))
    return G

def read_digraph(d):
    D = nx.DiGraph()
    D.graph["type"] = d["type"]
    D.graph["weighted"] = d["weighted"]
    for n in d["nodes"]:
        D.add_node(n["tag"])
    for e in d["edges"]:
        if d["weighted"]:
            D.add_edge(e["src"], e["dest"], weight = e["weight"], tag = e["tag"])
            print("added edge")
        else:
            D.add_edge(e["src"], e["dest"], tag = e["tag"])
    
    print(type(D.nodes(data=True)))
    print(type(D.edges(data=True)))
    return D

def read_network(net):
    D = nx.DiGraph()
    D.graph["type"] = net["type"]
    for n in net["nodes"]:
        q = float('inf')
        r = 0
        if "capacity" in n:
            q = n["capacity"]
        if "restriction" in n:
            r = n["restriction"]
        
        D.add_node(n["tag"], capacity=q, restriction=r)
    
    for e in net["edges"]:
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
        
        D.add_edge(e["src"], e["dest"], tag = e["tag"], capacity = q, restriction = r,
                    flow = f, cost = c)
    
    print(type(D.nodes(data=True)))
    print(type(D.edges(data=True)))
    return D

def read_file(result, algorithm):
    g = json.load(open(result))
    if g["type"] == "graph":
        print(algorithm)
        return read_graph(g)
    elif g["type"] == "digraph":
        print(algorithm)
        return read_digraph(g)
    elif g["type"] == "network":
        print(algorithm)
        return read_network(g)
    else:
        return None
    
# Read 