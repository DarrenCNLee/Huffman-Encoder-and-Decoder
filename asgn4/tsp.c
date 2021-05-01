#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK   4096 // code inspired by Eugene's lab section on 4/27
#define OPTIONS "hvui:o:"

// calls is number of calls
// verbose is a flag for verbose printing
// hamiltonian is a flag for whether or not a Hamiltonian path has been found
uint32_t calls = 0, verbose = 0, hamiltonian = 0;

// pseudocode for dfs given by Professor Long in assignment pdf
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    calls++;
    uint32_t x; // used for popping vertices
    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    for (uint32_t w = 0; w < graph_vertices(G); w++) {
        if ((path_length(curr) >= path_length(shortest)) && (path_length(shortest) != 0)) {
            continue; // skip paths that are longer than shortest path
        }
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) {
            dfs(G, w, curr, shortest, cities, outfile);
        }
        if ((path_vertices(curr) == graph_vertices(G)) && (graph_has_edge(G, v, START_VERTEX))) {
            path_push_vertex(curr, START_VERTEX, G);
            hamiltonian = 1; // set hamiltonian flag to 1 if a Hamiltonian path is found
            if ((path_length(shortest) == 0) || (path_length(curr) < path_length(shortest))) {
                path_copy(shortest, curr);
                if (verbose) { // print out each path if verbose mode is on
                    fprintf(outfile, "Path length: %" PRIu32 "\n", path_length(shortest));
                    fprintf(outfile, "Path: ");
                    path_print(shortest, outfile, cities);
                }
            }
            path_pop_vertex(curr, &x, G);
        }
    }
    path_pop_vertex(curr, &v, G);
    graph_mark_unvisited(G, v);
}

int main(int argc, char **argv) {
    char buffer[BLOCK]; // code influenced by Eugene's lab section on 4/27
    FILE *infile = stdin, *outfile = stdout; // defaults for infile and outfile
    uint32_t help = 0, undirect = 0;
    int opt, c, i, j, k, n;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            if (!help) {
                help = 1; // flag to print help message
            }
            break;
        case 'v':
            if (!verbose) {
                verbose = 1; // flag to use verbose mode
            }
            break;
        case 'u':
            if (!undirect) {
                undirect = 1; // undirected value for graph_create
            }
            break;
        case 'i': infile = fopen(optarg, "r"); break; // open infile
        case 'o': outfile = fopen(optarg, "w"); break; // open outfile
        }
    }
    if (infile == NULL) {
        fprintf(stderr,
            "Error: failed to open infile.\n"); // print error message if opening infile failed
        return 1;
    }
    if (outfile == NULL) {
        fprintf(stderr,
            "Error: failed to open outfile.\n"); // print error message if opening outfile failed
        return 1;
    }
    if (help) { // code for help message inspired by resources repository message
        fprintf(outfile, "SYNOPSIS\n");
        fprintf(outfile, "  Traveling Salesman Problem using DFS.\n");
        fprintf(outfile, "\n");
        fprintf(outfile, "USAGE\n");
        fprintf(outfile, "  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
        fprintf(outfile, "\n");
        fprintf(outfile, "OPTIONS\n");
        fprintf(outfile, "  -u             Use undirected graph.\n");
        fprintf(outfile, "  -v             Enable verbose printing.\n");
        fprintf(outfile, "  -h             Program usage and help.\n");
        fprintf(outfile, "  -i infile      Input containing graph (default: stdin)\n");
        fprintf(outfile, "  -o outfile     Output of computed path (default: stdout)\n");
        return 0;
    }
    fscanf(infile, "%d", &n); // read number of vertices
    if (n > VERTICES) { // print error if number of vertices is too large
        fprintf(outfile, "Error: malformed number of vertices.\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }
    if (n <= 1) { // if there is <= 1 vertex, there is nowhere to go
        fprintf(outfile, "There's nowhere to go.\n");
        fclose(infile);
        fclose(outfile);
        return 1;
    }
    char *cities[n];
    fgets(buffer, BLOCK, infile); // go to next line in input file
    for (int i = 0, j = 1; j <= n; i++, j++) {
        fgets(buffer, BLOCK, infile); // code influenced by Eugene's lab section on 4/27
        strtok(buffer, "\n"); // remove new line character from city names
        cities[i] = strdup(buffer); // initialize the names in the cities array
    }
    Graph *G = graph_create(n, undirect);
    // code influenced by Eugene's lab section on 4/27
    while ((c = fscanf(infile, "%d %d %d \n", &i, &j, &k)) != EOF) { // read the rest of the file
        if (c != 3) { // code influenced by Eugene's lab section on 4/27
            fprintf(stderr, "Error: malformed edge.\n"); // print error message
            fclose(infile);
            fclose(outfile);
            for (int i = 0; i < n; i++) { // code influenced by Eugene's lab section on 4/27
                free(cities[i]);
            }
            return 1;
        }
        graph_add_edge(G, i, j, k);
    }
    Path *curr = path_create();
    Path *shortest = path_create();
    dfs(G, START_VERTEX, curr, shortest, cities, outfile);
    if (!hamiltonian) {
        fprintf(stderr, "No Hamiltonian path found\n");
        fprintf(outfile, "Total recursive calls: %" PRIu32 "\n", calls);
        fclose(infile);
        fclose(outfile);
        for (int i = 0; i < n; i++) { // code influenced by Eugene's lab section on 4/27
            free(cities[i]);
        }
        path_delete(&curr);
        path_delete(&shortest);
        graph_delete(&G);
        return 1;
    }
    fprintf(outfile, "Path length: %" PRIu32 "\n", path_length(shortest));
    fprintf(outfile, "Path: ");
    path_print(shortest, outfile, cities);
    fprintf(outfile, "Total recursive calls: %" PRIu32 "\n", calls);
    for (int i = 0; i < n; i++) { // code influenced by Eugene's lab section on 4/27
        free(cities[i]);
    }
    fclose(infile);
    fclose(outfile);
    path_delete(&curr);
    path_delete(&shortest);
    graph_delete(&G);
    return 0;
}
