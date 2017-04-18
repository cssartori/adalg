# Implementing Dijkstra Algorithm using Heaps #

This repository contains the implementation of the Dijkstra Algorithm using the data structure Heaps. For while the algorithm uses k-Heaps, that is, heaps where each node can have up to k children, where k is a parameter.

## Compiling ##

The C++11 code can be compiled using a Makefile inside the repository. Three executables are generated: dijkstra, exp and gen.

* dijkstra: calls the algorithm dijkstra passing two nodes, a source and a target, returning the distance between them;
* exp: used to run several experiments over the algorithm and data structure, more details can be obtained within the executable;
* gen: a random graph generator, which generates a graph given a number of nodes, in a way that is is not necessarily complete, but highly connected.

## About ##
Done by Carlo S. Sartori
Class "CMP 588 - Advanced Algorithms", at UFRGS, 2017/1.