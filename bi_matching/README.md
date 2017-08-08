# Bipartide Matching #

Implementation of the Hopcroft-Karp algorithm for maximum matching in unweighted bipartide graphs. 

The algorithm uses both BFS and DFS search algorithms to select the next path to increase.

## Reduction from Maximum Flow ##

There is also an algorithm to compute the maximum matching using the reduction from the Maximum Flow problem, considering the max flow on each edge 1.
The algorithms used to solve the reduction are: Ford-Fulkerson, by *fattest path* strategy; and Push-Relabel.
