import dash
import dash_core_components as dcc
import dash_html_components as html
import dash_cytoscape as cyto
import dash_bootstrap_components as dbc
from dash.dependencies import Input, Output, State

#from nagui import app

import numpy as np
import networkx as nx
import controller


#--- Global variables

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

app = dash.Dash(
    __name__,
    external_stylesheets=external_stylesheets
)

#vis_height = '750px'
current_graph = nx.DiGraph()
original_graph = nx.DiGraph()
result_graph = nx.DiGraph()
graph_elements=[]
edges=[]
nodes=[]
file_id = 0
info = ''
styles = {
    'pre': {
        'border': 'thin lightgrey solid',
        'overflowX': 'scroll'
    }
}


#--- End of global variables

#--- GUI

# external_stylesheets = [dbc.themes.BOOTSTRAP] #['https://codepen.io/chriddyp/pen/bWLwgP.css']
# app = dash.Dash(__name__, external_stylesheets=external_stylesheets)

app.layout = html.Div(children=[
    html.Div(children=[
        dbc.Row([
            dbc.Col([
                html.H1('Networks', className='m-4', id='header-graph',style={'textAlign': 'center'})
            ], width=3),
            dbc.Col([
                dcc.Link('Graph ', href='/', className='btn btn-primary m-2'),
                html.H4(' '),
                dcc.Link('Digraphs', href='/', className='btn btn-primary m-2')
            ], width=2, style={'textAlign': 'center'})
        ], justify='around', align='center')
    ]),
    html.Table(children=[
        #html.Thead(children=[
        #   html.Th('', id='additional-info-graph', className='mx-3') 
        #]),
        #MENU
        html.Tbody(children=[
            # Agorithm select
            html.Td(children=[
                html.H5('Algorithm', className='m-4', id='header-algorithm',style={'textAlign': 'center'}),
                html.Tr(children=[
                    html.Td(children=[
                        dcc.Dropdown(
                            id='drop-algo-graph',
                            options=[
                                {'label': 'Ford-Fulkerson', 'value': 10},
                                {'label': 'Primal', 'value': 11},
                                {'label': 'Dual', 'value': 12},
                                {'label': 'Simplex', 'value': 13}
                            ],
                            clearable=False,
                            value=10
                        )
                    ])
                ], style={'width': 200}),
                #dropdown select
                html.Tr(children=[
                   html.Td(children=[
                        html.H6("target: ")
                    ]),
                    html.Td(children=[
                        dbc.Input(id='target-graph', type='number', className='mx-1 my-1')
                    ]) 
                ]),
                html.Tr(children=[
                    # dbc.Button('Previous step', color='info', id='btn-prev-graph', className='mx-2'),
                    # dbc.Button('Next step', color='info', id='btn-next-graph', className='mx-2'),
                    html.Td(children=[
                        dbc.Button('Run', color='info', id='btn-run-graph', className='mx-2')
                    ]),
                    html.Td(children=[
                        dbc.Button('Restore', color='warning', id='btn-reset-graph', className='mx-2')

                    ]),
                    html.Td(children=[
                        dbc.Button('Clear', color='warning', id='btn-empty-graph', className='mx-2')
                    ])
                ])
            ]),
            # ADD VERTEX
            html.Td(children=[
                html.Tr(children=[
                    html.H5('Add Node', className='m-4', id='header-vertex',style={'textAlign': 'center'})
                ]),
                html.Tr(children=[
                    html.Td(children=[
                        html.H6("tag: ")
                    ]),
                    html.Td(children=[
                        dbc.Input(id='vertex-graph', type='text', className='mx-1 my-1')
                    ])
                ]),
                html.Tr(children=[
                   html.Td(children=[
                        html.H6("capacity: ")
                    ]),
                    html.Td(children=[
                        dbc.Input(id='capacity-node-graph', type='number', className='mx-1 my-1')
                    ]) 
                ]),
                html.Tr(children=[
                   html.Td(children=[
                        html.H6("restriction: ")
                    ]),
                    html.Td(children=[
                        dbc.Input(id='restriction-node-graph', type='number', className='mx-1 my-1')
                    ]) 
                ]),
                html.Tr(children=[
                    dcc.Dropdown(
                            id='drop-type-node-graph',
                            options=[
                                {'label': 'Normal', 'value': 0},
                                {'label': 'Source', 'value': 1},
                                {'label': 'Terminus', 'value': 2}
                            ],
                            clearable=False,
                            value=0
                        )
                ]),
                html.Tr(children=[
                    dbc.Button('Add', color='primary', id='btn-vertex-graph', className='my-2')
                ])
            ]),
            # ADD EDGE
            html.Td(children=[
                html.Tr(children=[
                    html.H5('Add Edge', className='m-4',style={'textAlign': 'center'})
                ]),
                html.Tr(children=[
                    html.Td(children=[
                        html.H6(' source: ')#,
                    ]),
                    html.Td(children=[
                        dbc.Input(id='source-graph', type='text', className='mx-1 my-1')
                    ])
                ]),
                html.Tr(children=[
                   html.Td(children=[
                        html.H6(' destination: ')#,
                    ]),
                    html.Td(children=[
                        dbc.Input(id='terminus-graph', type='text', className='mx-1 my-1')
                    ]) 
                ]),
                html.Tr(children=[
                    html.Td(children=[
                        html.H6("capacity: ")
                    ]),
                    html.Td(children=[
                        dbc.Input(id='capacity-edge-graph', type='number', className='mx-1 my-1')
                    ]),
                ]) 
            ]),
            # ADD EDGE
            html.Td(children=[
                html.Tr(children=[
                        html.H6("restriction: ")
                    ]),
                    html.Tr(children=[
                        dbc.Input(id='restriction-edge-graph', type='number', className='mx-1 my-1')
                    ]),
                html.Tr(children=[
                    html.H6(' cost: ')#,
                ]),
                html.Tr(children=[
                    dbc.Input(id='cost-edge-tag', type='number', className='mx-1 my-1')
                ]),
                html.Tr(children=[
                    html.Br(),
                    dbc.Button('Add', color='primary', id='btn-edge-graph', className='my-1')
                ])
            ]),
            # REMOVE VERTEX
            html.Td(children=[
                html.Tr(children=[
                    html.H4('Remove Node', className='m-4',style={'textAlign': 'center'})
                ]),
                html.Tr(children=[
                    html.Td(children=[
                        html.H6("tag: ")
                    ]),
                    html.Td(children=[
                        dbc.Input(id='rm-vertex-graph', type='text', className='mx-1 my-1')
                    ])
                ]),
                html.Tr(children=[
                    html.Br(),
                    dbc.Button('Remove', color='primary', id='btn-rm-vertex-graph', className='my-2')
                ])
            ]),
            # REMOVE EDGE
            html.Td(children=[
                #html.H5('Remove edge:')
                #html.H6('to'),
                html.Tr(children=[
                    html.H4('Remove Edge', className='m-4',style={'textAlign': 'center'})
                ]),
                html.Tr(children=[
                    html.Td(children=[
                        html.H6("source: ")
                    ]),
                    html.Td(children=[
                        dbc.Input(id='rm-source-graph', type='text', className='mx-1 my-1')
                    ])
                ]),
                html.Tr(children=[
                    html.Td(children=[
                        html.H6("destination: ")
                    ]),
                    html.Td(children=[
                         dbc.Input(id='rm-terminus-graph', type='text', className='mx-1 my-1')
                    ])
                ]),
                html.Tr(children=[
                    dbc.Button('Remove', color='primary', id='btn-rm-edge-graph', className='my-2')
                ])
            ])
        ])
    ]),
    html.Table(children=[
        html.Tbody(children=[
            html.Td(children=[
                html.H3(" ", style={'textAlign': 'center'}, id='info-graph', className='mx-3')
            ]),   
            html.Td(children=[
                html.H3(" ", style={'textAlign': 'center'}, id='additional-info-graph', className='mx-3')
            ])   
        ])
    ], style={"width":2000}),
    html.Div(children=[
        html.Table(children=[
            html.Thead(children=[
                html.Th(children=[
                    html.H4("Network", style={'textAlign': 'center',"width":2000, "heigth":1200})
                ],style={"width":2000, "heigth":1200})#,
                #html.Th(children=[
                #    html.H4("Result", style={'textAlign': 'center'})
                #å])
            ],style={"width":2000, "heigth":1200}),
            html.Tbody(children=[
                html.Td(children=[
                    cyto.Cytoscape(
                    id='graph',
                    layout={
                        'name': 'cose'
                    },
                    style={
                        'width': '100%',
                        'height': '750px'
                    },
                    stylesheet=[
                        {
                            'selector': 'node',
                            'style': {
                                'label': 'data(label)'
                            }
                        },
                        {
                            'selector': 'edge',
                            'style': {
                                'label': 'data(capacity)',
                                'curve-style': 'bezier',
                                'target-arrow-shape': 'vee'
                            }
                        },
                    ],
                    elements=[]
                )
                ],style={"width":2000, "heigth":1200})
            ])
        ])
    ])
])

#--- End of GUI

#--- Callbacks
"""
Updating the graph every time a vertex or an edge are added/removed.
"""
@app.callback(
    Output(component_id='graph', component_property='elements'),
    [Input(component_id='btn-vertex-graph', component_property='n_clicks_timestamp'),
     Input(component_id='btn-edge-graph', component_property='n_clicks_timestamp'),
     Input(component_id='btn-rm-vertex-graph', component_property='n_clicks_timestamp'),
     Input(component_id='btn-rm-edge-graph', component_property='n_clicks_timestamp'),
     Input(component_id='btn-run-graph', component_property='n_clicks_timestamp'),
     Input(component_id='btn-reset-graph', component_property='n_clicks_timestamp'),
     Input(component_id='btn-empty-graph', component_property='n_clicks_timestamp')],
    [State(component_id='vertex-graph', component_property='value'),
     State(component_id='capacity-node-graph', component_property='value'),
     State(component_id='restriction-node-graph', component_property='value'),
     State(component_id='capacity-edge-graph', component_property='value'),
     State(component_id='restriction-edge-graph', component_property='value'),
     State(component_id='cost-edge-tag', component_property='value'),
     State(component_id='source-graph', component_property='value'),
     State(component_id='terminus-graph', component_property='value'),
     State(component_id='rm-vertex-graph', component_property='value'),
     State(component_id='rm-source-graph', component_property='value'),
     State(component_id='rm-terminus-graph', component_property='value'),
     #State(component_id='weight-graph', component_property='value'),
     State(component_id='target-graph', component_property='value'),
     State('drop-algo-graph', 'value'),
     State('drop-type-node-graph', 'value'),
     #State('target-graph', 'value'),
     State('graph', 'elements')]
     #State('results-graph',result_elements)]
)
def update_graph(btn_vertex, btn_edge, btn_rm_v, btn_rm_e, btn_run, btn_reset, 
                btn_empty, vertex_value, capacity_node, restriction_node, source, terminus,
                capacity_edge, restriction_edge, cost_edge, rm_vertex, rm_source, 
                rm_terminus, type_node, algorithm, elements):
    global current_graph
    global file_id
    global original_graph
    global result_graph
    global result_elements
    global nodes
    global edges
    global info

    info = ''
    buttons = np.array([btn if btn is not None else 0 for btn in (btn_vertex, btn_edge, btn_rm_v, btn_rm_e, btn_run, btn_reset, 
                        btn_empty)])
    btn_pressed = np.argmax(buttons)

    # Add vertex button
    if btn_vertex is not None and btn_pressed == 0 and vertex_value != "":
        if not current_graph.has_node(vertex_value):
            print(vertex_value)
            print(capacity_node)
            print(restriction_node)
            print(type_node)
            #si tiene ambos
            if type_node == 0:
                if capacity_node is not None and restriction_node is not None:
                    current_graph.add_node(vertex_value, capacity=capacity_node, restriction=restriction_node, label=vertex_value, type="normal")
                #si tiene capacidad
                elif capacity_node is not None:
                    current_graph.add_node(vertex_value, capacity=capacity_node, label=vertex_value,type="normal")
                #si tiene restriccion
                else:
                    current_graph.add_node(vertex_value, restriction=restriction_node, label=vertex_value,type="normal")
            #SOURCE
            elif type_node == 1:
                if capacity_node is not None and restriction_node is not None:
                    current_graph.add_node(vertex_value, capacity=capacity_node, restriction=restriction_node, type="source", label=f"+ {vertex_value}")
                #si tiene capacidad
                elif capacity_node is not None:
                    current_graph.add_node(vertex_value, capacity=capacity_node, type="source", label=f"+ {vertex_value}")
                #si tiene restriccion
                else:
                    current_graph.add_node(vertex_value, restriction=restriction_node, type="source", label=f"+ {vertex_value}")
            #TERMINUS
            else:
                if capacity_node is not None and restriction_node is not None:
                    current_graph.add_node(vertex_value, capacity=capacity_node, restriction=restriction_node, type="terminus", label=f"{vertex_value} -")
                #si tiene capacidad
                elif capacity_node is not None:
                    current_graph.add_node(vertex_value, capacity=capacity_node, type="terminus", label=f"{vertex_value} -")
                #si tiene restriccion
                else:
                    current_graph.add_node(vertex_value, restriction=restriction_node, type="terminus", label=f"{vertex_value} -")
            
            elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
            elements = elements['elements']['nodes'] + elements['elements']['edges']
        else:
            info = 'Node {} is already on the graph'.format(vertex_value)


    # Add edge button
    elif btn_edge is not None and btn_pressed == 1 and source != "" and terminus != "":


        # 
        if current_graph.has_node(source) and current_graph.has_node(terminus):
            #capacidad y restriccion y costo
            if capacity_edge is not None and restriction_edge is not None and cost_edge is not None:
                current_graph.add_edge(source, terminus, capacity=capacity_edge, restriction=restriction_edge, cost=cost_edge)
            #capacidad y costo
            elif capacity_edge is not None and cost_edge is not None:
                current_graph.add_edge(source, terminus, capacity=capacity_edge, cost=cost_edge)
            #capacidad y restriccion
            elif capacity_edge is not None and restriction_edge is not None:
                current_graph.add_edge(source, terminus, capacity=capacity_edge, restriction=restriction_edge)
            #restriccion y costo
            elif restriction_edge is not None and cost_edge is not None:
                current_graph.add_edge(source, terminus, restriction=restriction_edge, cost=cost_edge)

            elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
            elements = elements['elements']['nodes'] + elements['elements']['edges']

        
        elif not current_graph.has_node(source) and current_graph.has_node(terminus):
            info = 'Node {} is not on the graph'.format(source)
        elif current_graph.has_node(source) and not current_graph.has_node(terminus):
            info = 'Node {} is not on the graph'.format(terminus)
        else:
            info = 'Nodes {} and {} are not on the graph'.format(source, terminus)
   
    # Delete vertex button
    elif btn_rm_v is not None and btn_pressed == 2 and rm_vertex != "":
        if current_graph.has_node(rm_vertex):
            current_graph.remove_node(rm_vertex)
            elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
            elements = elements['elements']['nodes'] + elements['elements']['edges']
        else:
            info = 'Node {} is not on the graph'.format(rm_vertex)
    
    # Delete edge button
    elif btn_rm_e is not None and btn_pressed == 3 and rm_source != "" and rm_terminus != "":
        if current_graph.has_node(rm_source) and current_graph.has_node(rm_terminus) and current_graph.has_edge(rm_source, rm_terminus):
            current_graph.remove_edge(rm_source, rm_terminus)
            elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
            elements = elements['elements']['nodes'] + elements['elements']['edges']
        elif not current_graph.has_node(rm_source) and current_graph.has_node(rm_terminus):
            info = 'Node {} is not on the graph'.format(rm_source)
        elif current_graph.has_node(rm_source) and not current_graph.has_node(rm_terminus):
            info = 'Nodes {} is not on the graph'.format(rm_terminus)
        elif not current_graph.has_node(rm_source) and not current_graph.has_node(rm_terminus):
            info = 'Nodes {} and {} are not on the graph'.format(rm_source, rm_terminus)
        else:
            info = "There is not an edge between nodes {} and {}".format(rm_source, rm_terminus)
    
    # Run algorithm button
    elif btn_run is not None and btn_pressed == 4:
        
        print(current_graph.nodes)
        print(current_graph.edges)

        #if initial_tag != "":

            ## Dijkstra
#            if algorithm == 8:
                # if algorithm needs parameter, enter it
#                params = tuple()
#                if termination_tag != "":
                    #params[1] = termination_tag
#                    params = (initial_tag)
#                else:
#                    params = (initial_tag, termination_tag)
#                
#                res, info, g = controller.run_digraph(current_graph, algorithm, params)
                
#                print(g)
#                print(info)
#                if res:

#                    nodes = g#nx.readwrite.json_graph.cytoscape_data(g)
#                    print(nodes)
                    #edges = g.edges


                #info = i
                # controller.run_graph(current_graph)
                #file_path = file.save_graph(current_graph, file_id)
#                original_graph = current_graph
#                current_graph = g
                #sbp.run(["./lib/bin/graph.out", file_path, str(file_id), algorithm])
                #result, is_a_graph, info = file.load_graph(file_id)
                #if is_a_graph:
                #    current_graph = result
                #    file_id += 1
                #else:
                #    info = result
                #controller.receive_graph(current_graph)
#                elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
#                elements = elements['elements']['nodes'] + elements['elements']['edges']
            # Floyd
#            else:
               # if algorithm needs parameter, enter it
#                params = (initial_tag)
#                res, info, g = controller.run_digraph(current_graph, algorithm, params)
                
#                print(g)
#                print(info)
#                if res:
#                    nodes = g
#                    print(nodes)
#                original_graph = current_graph
#                current_graph = g
#                elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
#                elements = elements['elements']['nodes'] + elements['elements']['edges'] 

#        else:
#            info = "Please enter initial tag"

    # Restore graph button (prolly not need)
    elif btn_reset is not None and btn_pressed == 5:
        current_graph = original_graph
        elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
        elements = elements['elements']['nodes'] + elements['elements']['edges']
        
        
    # Clear graph button
    elif btn_empty is not None and btn_pressed == 6:
        current_graph.clear()
        elements = nx.readwrite.json_graph.cytoscape_data(current_graph)
        elements = elements['elements']['nodes'] + elements['elements']['edges']
    return elements

"""
Displaying additional information,
"""
@app.callback(
    Output('additional-info-graph', 'children'),
    [Input('graph', 'elements')]
)
def update_additional_info(graph):
    global info
    return info

"""
Changing the graph's stylesheet everytime there's a change between types.
"""
@app.callback(
    Output('graph', 'stylesheet'),
    [Input('graph', 'elements')]
)
def update_graph_stylesheet(graph):
    global current_graph
    if type(current_graph) == nx.classes.graph.Graph:
        return [
            {
                'selector': 'node',
                'style': {
                    'label': 'data(id)'
                }
            },
            {
                'selector': 'edge',
                'style': {
                    'label': 'data(weight)',
                    'curve-style': 'bezier',
                }
            }
        ]
    else:
        return [
            {
                'selector': 'node',
                'style': {
                    'label': 'data(id)'
                }
            },
            {
                'selector': 'edge',
                'style': {
                    'label': 'data(weight)',
                    'curve-style': 'bezier',
                    'target-arrow-shape': 'vee'
                }
            }
        ]

"""
Changing the information displayed at the top of the page every time the graph
is changed.
"""
@app.callback(
    Output(component_id='info-graph', component_property='children'),
    [Input(component_id='graph', component_property='elements')]
)
def update_graph_info(graph):
    return "Nodes: {} Edges: {} ".format(current_graph.number_of_nodes(), current_graph.number_of_edges())


"""
Resetting the Inputs every time their assigned button gets pressed.
"""
@app.callback(
    Output(component_id='vertex-graph', component_property='value'),
    [Input(component_id='btn-vertex-graph', component_property='n_clicks')]
)
def reset_vertex_input(n_clicks):
    return ""

@app.callback(
    Output(component_id='source-graph', component_property='value'),
    [Input(component_id='btn-edge-graph', component_property='n_clicks')]
)
def reset_source_input(n_clicks):
    return ""

@app.callback(
    Output(component_id='terminus-graph', component_property='value'),
    [Input(component_id='btn-edge-graph', component_property='n_clicks')]
)
def reset_terminus_input(n_clicks):
    return ""

#@app.callback(
#    Output(component_id='weight-graph', component_property='value'),
#    [Input(component_id='btn-edge-graph', component_property='n_clicks')]
#)
#def reset_weight_input(n_clicks):
#    return 1

@app.callback(
    Output(component_id='rm-vertex-graph', component_property='value'),
    [Input(component_id='btn-rm-vertex-graph', component_property='n_clicks')]
)
def reset_rm_vertex_input(n_clicks):
    return ""

@app.callback(
    Output(component_id='rm-source-graph', component_property='value'),
    [Input(component_id='btn-rm-edge-graph', component_property='n_clicks')]
)
def reset_rm_source_input(n_clicks):
    return ""

@app.callback(
    Output(component_id='rm-terminus-graph', component_property='value'),
    [Input(component_id='btn-rm-edge-graph', component_property='n_clicks')]
)
def reset_rm_terminus_input(n_clicks):
    return ""





if __name__ == '__main__':
    app.run_server(host='0.0.0.0',debug=True, port=8050)
