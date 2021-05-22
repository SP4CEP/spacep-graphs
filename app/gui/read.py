import json
import networkx as nx

"""
Read a graph from a json file,
returns nx.Graph()
"""
def graph(g):
    # bool, info, graph
    G = nx.Graph()
    res = g["res"]
    info = ""
    if res:
        info = "Graph is connected"
    else:
        info = "Graph is disconnected"

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
    
    #print(type(G.nodes(data=True)))
    #print(type(G.edges(data=True)))
    return res, info, G
"""
Read a digraph from a json file,
returns nx.DiGraph()
"""
def digraph(d, params):
    res = d["res"]
    info ="Shortest paths with initial node: " + d["initial_tag"] 

    if params[1] is not "":
        info += ", destination tag: " + params[1]
    info += ", weight: " + str(d["weight"])
    
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
    return res, info, D
"""
Read a network from a json file,
returns nx.DiGraph()
"""
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

def read_partition(p):
    res = p["res"]
    info = ""
    g = nx.Graph()
    if res:
        P1=""
        P2=""
        for n in p["P1"]:
            P1 += (n + " ")
        for n in p["P2"]:
            P2 += (n+" ")
        
        info = "Partitions P1: " + P1 + "    P2: " + P2
        for n in p["P1"]:
            g.add_node(n)
        for n in p["P2"]:
            g.add_node(n)
    else:
        info = "Solution not found"
    
    return res, info, g

def read_forest(forest):
    info ="Graph is "
    res = forest["res"]
    master = nx.Graph()
    if res:
        info += "connected"
    else:
        info += "disconnected"
    
    for g in forest["forest"]:
        for n in g["nodes"]:
            master.add_node(n["tag"])
        for e in g["edges"]:
            master.add_edge(e["src"], e["dest"], weight = e["weight"])
    
    return res, info, master

def read_path(p):
    res = p["res"]
    info = ""
    g = nx.Graph()

    if res:
        path = ""
        nodes = p["path"]
        print(nodes)
        for n in nodes:
            g.add_node(n)
            path += (n + " ")
        
        info = "Euler's path found: " + path

        for i in range(len(nodes) - 1):
            g.add_edge(nodes[i], nodes[i+1])
    else:
        info = "Solution not found"

    return res, info, g

def read_graph(result, algorithm):
    g = json.load(open(result))
    if g["type"] == "graph":
        print(algorithm)
        return graph(g)
    elif g["type"] == "partition":
        return read_partition(g)
    elif g["type"] == "forest":
        return read_forest(g)
    elif g["type"] == "path":
        return read_path(g)
    else:
        return None, None, None


###########################################################
def read_cycle(p):
    res = p["res"]
    info = ""
    g = nx.DiGraph()
    path = ""
    nodes = p["nodes"]
    print(nodes)
    for n in nodes:
        g.add_node(n)
        path += (n + " ")
    
    info = "Found cycle: " + path + " with length: " + str(p["cycle_len"])

    for i in range(len(nodes) - 1):
        g.add_edge(nodes[i], nodes[i+1])
    g.add_edge(nodes[0], nodes[-1])

    return res, info, g

###########################################################

def read_paths(forest):
    res = forest["res"]
    master = nx.DiGraph()
    info ="Shortest paths with initial node " + forest["initial_tag"] + ": "
    for g in forest["paths"]:
        if len(g["edges"]) != 0:
            if forest["paths"][0] == g:
                info += " ["
            else:
                info += ", ["
        for n in g["nodes"]:
            master.add_node(n["tag"])
        for e in g["edges"]:
            master.add_edge(e["src"], e["dest"], weight = e["weight"])
            if len(g["edges"]) != 0:
                src = e["src"]
                dest = e["dest"]
                if g["edges"][-1] == e:
                    info += f"({src},{dest})"
                else:
                    info += f"({src},{dest}), "
                    
        if len(g["edges"]) != 0:
            info += "] "
    
    return res, info, master

###########################################################
def read_digraph(result, algorithm, params):
    g = json.load(open(result))
    if g["type"] == "digraph":
        print(algorithm)
        return digraph(g, params)
    elif g["type"] == "cycle":
        return read_cycle(g)
    elif g["type"] == "short_paths":
        return read_paths(g)
    elif g["type"] == "disconnected":
        return False, "Graph is not connected", g
    else:
        return None, None, None

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
    elif g["type"] == "partition":
        return read_partition(g)
    #elif g["type"] == "forest":
    #elif g["type"] == "path":
    else:
        return None
    
# Read 