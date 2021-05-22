# spacep-graphs

Implementation of a graph and multiple algorithms for the Network Analysis course at UNISON 2021-1


### run:

1. Build image

```
docker build --tag='spacep' .
```

2. make `bin` director inside repo root

```
docker run -it --name graphs -p 8050:8050 -v $PWD:/workspace/spacep-graphs spacep
```
3. inside cd to repo and run:

```
make
```

4. to run graphs (hi):

graphs:

```
python3 app/gui/graph.py
```


digraphs:

```
python3 app/gui/digraph.py
```

network:

```
python3 app/gui/network.py
```

#### rerun:

```
docker start -it graphs
```
