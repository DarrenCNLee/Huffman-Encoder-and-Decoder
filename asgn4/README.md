Darren Lee

CruzID: danalee

Spring 2021
# Assignment 4: The Circumnavigations of Denver Long
This program implements a depth-first search function that solves
the Traveling Salesman Problem and finds the shortest 
Hamiltonian Path for a graph  if it exists. The program accepts a maximum 
of 26 vertices for a graph.

## Build
	$ make
## Running
	$ ./tsp [-hvu] [-i infile] [-o outfile]
	
	-u Specifies that the graph is undirected
	-v Enables verbose printing so all successively shortest 
	Hamiltonian paths are printed
	-h Specifies to print usage and help message then exits program
	-i infile Specifies the file for input, default is stdin
	-o outfile Specifies the file for output, default is stdout
## Cleaning
	$ make clean
## Files
	Design.pdf - This design document has th purpose, layout, functionality,
	and draft work for the program.

	graph.h - Contains the interface for the graph ADT

	graph.c - Contains the program code for the graph ADT and its functions

	stack.h - Contains the interface for the stack ADT

	stack.c - Contains the program code for the stack ADT and its functions

	path.h - Contains the interface for the path ADT

	path.c - Contains the program code for the path ADT and its functions

	vertices.h - Contains definitions for the START_VERTEX and VERTICES
	macros

	tsp.c - Contains program code for the dfs function and the solution
	to the Traveling Salesman Problem

	Makefile - Contains directives for building and cleaning the tsp program
