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
    #{'type': 'digraph', 'weighted': True}
    nodes = []
    edges =[]

    # Append nodes
    for n in G.nodes(data=True):
        print(n)
        nodes.append({"tag": n[0]})
    
    # Append edges
    for e in G.edges(data=True):
        print(e)
        edge = {
            "tag": e[2]['tag'],
            "src": e[0],
            "dest": e[1],
            "weight": e[2]['weight']
        }
        edges.append(edge)
    write = {
        "type": "digraph",
        "nodes": nodes,
        "edges": edges,
        "type": G.graph["type"],
        "weighted": G.graph["weighted"]
    }
    return write

def write_digraph(D):
    nodes = []
    edges =[]

    # Append nodes
    for n in D.nodes(data=True):
        print(n)
        nodes.append({"tag": n[0]})
    
    # Append edges
    for e in D.edges(data=True):
        print(e)
        edge = {
            "tag": e[2]['tag'],
            "src": e[0],
            "dest": e[1],
            "weight": e[2]['weight']
        }
        edges.append(edge)
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

    # Append nodes
    for n in D.nodes(data=True):
        print(n)
        nodes.append({
            "tag": n[0],
            "restriction": n[1]['restriction'],
            "capacity": n[1]['capacity']
            })
    
    # Append edges
    for e in D.edges(data=True):
        print(e)
        edge = {
            "tag": e[2]['tag'],
            "src": e[0],
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
        "edges": edges,
        "type": D.graph["type"]
    }
    return write