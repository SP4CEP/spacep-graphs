# spacep-graphs

Implementation of a graph and multiple algorithms for the Network Analysis course at UNISON 2021-1


### run:


```
docker build --tag='spacep' .
```


```
docker run -it --name graphs -p 8050:8050 -v $PWD:/workspace/spacep-graphs spacep
```
inside change dir to repo and run:

```
make
```

to run graphs (hi):

```
python3 app/gui/testdash.py
```

#### rerun:

```
docker start -it graphs
```
