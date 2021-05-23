import json
import networkx as nx

"""
Read a graph from a json file,
returns nx.MultiGraph()
"""
def graph(g, algorithm):
    # bool, info, graph
    G = nx.MultiGraph()
    res = g["res"]
    info = ""
    if res:
        info = "Graph is connected"
    else:
        info = "Graph is disconnected"
    
    if algorithm == 6 or algorithm == 7:
        w=g["weight"]
        info += f", weight = {w}"

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
    
    return res, info, G
"""
Read a digraph from a json file,
returns nx.MultiDiGraph()
"""
def digraph(d, params):
    res = d["res"]
    info ="Shortest paths with initial node: " + d["initial_tag"] 

    if len(params) != 1:
        info += ", destination tag: " + params[1]
    info += ", weight: " + str(d["weight"])
    
    D = nx.MultiDiGraph()
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
returns nx.MultiDiGraph()
"""
def network(net):
    D = nx.MultiDiGraph()
    D.graph["type"] = net["type"]
    for n in net["nodes"]:
        q = float('inf')
        r = 0
        tag = n["tag"]
        if n["capacity"] == 999999999:
            q = float('inf')
        else:
            q = n["capacity"]
        r = n["restriction"]

        if "type" in n:
            if n["type"] == "source":
                D.add_node(tag, capacity=q, restriction=r, type="source", info=f"+{tag}, [{q},{r}]")
            else: #n["type"] == "terminus":
                D.add_node(tag, capacity=q, restriction=r, type="terminus", info=f"-{tag}, [{q},{r}]")
        else:
            D.add_node(tag, capacity=q, restriction=r, type="normal", info=f"{tag}, [{q},{r}]")

    for e in net["edges"]:
        q = 0

        if e["capacity"] == 999999999:
            q = float('inf')
            r = e["restriction"]
            f = e["flow"]
            c = e["cost"]
            D.add_edge(e["src"], e["dest"], tag = e["tag"], capacity = float('inf'), restriction = e["restriction"],flow = e["flow"], cost = e["cost"], info=f"[q: {q} r: {r} c: {c} f: {f}]")
        else:
            q=e["capacity"]
            r = e["restriction"]
            f = e["flow"]
            c = e["cost"]
            D.add_edge(e["src"], e["dest"], tag = e["tag"], capacity = e["capacity"], restriction = e["restriction"],flow = e["flow"], cost = e["cost"], info=f"[q: {q} r: {r} c: {c} f: {f}]")
        
    
    print("edges added")
    print(D.edges(data=True))
    return D

def read_partition(p):
    res = p["res"]
    info = ""
    g = nx.MultiGraph()
    if res:
        P1=""
        P2=""
        for n in p["P1"]:
            P1 += (n + " ")
        for n in p["P2"]:
            P2 += (n+" ")
        
        info = "Partitions P1: " + P1 + "    P2: " + P2
        for n in p["P1"]:
            g.add_node(n, info=f"{n}, [P1]")
        for n in p["P2"]:
            g.add_node(n, info=f"{n} [P2]")
    else:
        info = "Solution not found"
    
    return res, info, g

def read_forest(forest, algorithm):
    info ="Graph is "
    res = forest["res"]
    master = nx.MultiGraph()
    if res:
        info += "connected"
    else:
        info += "disconnected"
    print("running algo: " + str(algorithm))
    if algorithm == 6 or algorithm == 7:
        w=forest["weight"]
        info += f", weight = {w}"
    
    for g in forest["forest"]:
        for n in g["nodes"]:
            master.add_node(n["tag"])
        for e in g["edges"]:
            master.add_edge(e["src"], e["dest"], weight = e["weight"])
    
    return res, info, master

def read_path(p):
    res = p["res"]
    info = ""
    g = nx.MultiGraph()

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
        return graph(g, algorithm)
    elif g["type"] == "partition":
        return read_partition(g)
    elif g["type"] == "forest":
        return read_forest(g, algorithm)
    elif g["type"] == "path":
        return read_path(g)
    else:
        return None, None, None


###########################################################
def read_cycle(p):
    res = p["res"]
    info = ""
    g = nx.MultiDiGraph()
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
    master = nx.MultiDiGraph()
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

###########################################################

def read_network(result, algorithm, params):
    n = result
    res = n["res"]
    info = ""
    graph_n = nx.MultiDiGraph()#network(n)

    #Ford Fulkerson
    if algorithm == 10:
        if res:
            graph_n = network(n)
            info = "Total flow: " + str(n["total_flow"])
        else:
            info = "Solution not found"
    #primal
    elif algorithm == 11:
        if res:
            graph_n=network(n)
            info = "Target flow: "+ str(n["target_flow"]) + " Optimal cost: " + str(n["optimal_cost"])
        else:
            info="Solution not found"
    #dual
    elif algorithm == 12:
        if res:
            graph_n=network(n)
            info = "Target flow: " + str(n["target_flow"]) + " Optimal cost: " + str(n["optimal_cost"])
        else:
            info="Solution not found"
    #simplex
    else:
        if res:
            graph_n=network(n)
            info = "Optimal cost: " + str(n["optimal_cost"])
        else:
            info = "Solution not found"
    return res, info, graph_n



###########################################################
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
    else:
        return None
    
# Read 