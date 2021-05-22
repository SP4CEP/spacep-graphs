import networkx as nx


#return dictionary to convert to json
def write_dict(G):
    if G.graph["type"] == "graph":
        return write_graph(G)
    elif G.graph["type"] == "digraph":
        return write_digraph(G)
    else:
        return write_network(G)
        
def write_graph(G):
    nodes = []
    edges =[]
    c = 0
    # Append nodes
    for n in G.nodes:
        print(n)
        nodes.append({"tag": n})
    
    # Append edges
    for e in G.edges(data=True):
        print(e)
        edge = {
            "tag": f'e{c}',
            "src": e[0],
            "dest": e[1],
            "weight": e[2]['weight']
        }
        edges.append(edge)
        c+=1

    write = {
        "type": "graph",
        "nodes": nodes,
        "edges": edges,
        "type": G.graph["type"],
        "weighted": G.graph["weighted"]
    }
    return write

def write_digraph(D):
    nodes = []
    edges =[]
    c = 0
    # Append nodes
    for n in D.nodes:
        print(n)
        nodes.append({"tag": n})
    
    # Append edges
    for e in D.edges(data=True):
        print(e)
        edge = {
            "tag": f'e{c}',
            "src": e[0],
            "dest": e[1],
            "weight": e[2]['weight']
        }
        edges.append(edge)
        c+=1
    write = {
        "type": "digraph",
        "nodes": nodes,
        "edges": edges,
        "type": D.graph["type"],
        "weighted": D.graph["weighted"]
    }
    return write

def write_network(D):
    nodes = []
    edges =[]
    c=0
    # Append nodes
    for n in D.nodes(data=True):
        print(n)
        node = {"tag": n[0]}

        node["restriction"] = n[1]['restriction']
        
        # NUEVE NUEVE NUEVEEEEEE
        if n[1]['capacity'] == float('inf'):
            node["capacity"]= 999999999
        else:
            node["capacity"]=n[1]['capacity']
        
        if n[1]['type'] == "source":
            node["type"]="source"
        if n[1]['type'] == "terminus":
            node["type"]="terminus"
        
        nodes.append(node)
        

    # Append edges
    for e in D.edges(data=True):
        print(e)
        edge = {
            "tag": f"e{c}",
            "src": e[0],
            "dest": e[1]
        }
        if e[2]['capacity'] == float('inf'):
            edge["capacity"] = 999999999 
        else:
            edge['capacity'] = e[2]['capacity']
        edge["restriction"] = e[2]['restriction']
        edge["cost"] = e[2]['cost']
        edge["flow"] = e[2]['flow']
        
        c+=1
        edges.append(edge)
    write = {
        "type": "network",
        "nodes": nodes,
        "edges": edges,
        "type": D.graph["type"]
    }
    return write