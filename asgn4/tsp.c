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
#define OPTIONS "hvui:p:"

uint32_t calls = 0;

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    calls++;
    graph_mark_visited(G, v);
    for (uint32_t w = v; w < graph_vertices(G); w++) {
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) {
            dfs(G, w, curr, shortest, cities, outfile);
        }
        if (path_vertices(curr) == graph_vertices(G) && !path_length(shortest)) {
            path_copy(shortest, curr);
        }
        if (path_vertices(curr) == graph_vertices(G) && path_length(curr) < path_length(shortest)) {
            path_copy(shortest, curr);
        }
    }
    graph_mark_unvisited(G, v);
}

int main(int argc, char **argv) {
    char buffer[BLOCK]; // code influenced by Eugene's lab section on 4/27
    FILE *infile = stdin, *outfile = stdout;
    uint32_t help, verbose, undirect, n;
    int opt, c, i, j, k;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            if (!help) {
                help = 1;
            }
            break;
        case 'v':
            if (!verbose) {
                verbose = 1;
            }
            break;
        case 'u':
            if (!undirect) {
                undirect = 1;
            }
            break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        }
    }
    if (infile == NULL) {
        fprintf(stderr, "failed to open");
        return 1;
    }
    fscanf(infile, "%" PRIu32, &n);
    char *cities[n];
    for (uint32_t i = 0; i < n; i++) {
        fgets(buffer, BLOCK, infile); // code influenced by Eugene's lab section on 4/27
        cities[i] = strdup(buffer);
    }
    fputs(buffer, outfile);

    Graph *G = graph_create(n, undirect);
    // code influenced by Eugene's lab section on 4/27
    while ((c = fscanf(infile, "%d %d %d \n", &i, &j, &k)) != EOF) {
        if (c != 3) {
            printf("malformed line\n");
            return 1;
        }
        graph_add_edge(G, i, j, k);
        //        fprintf(outfile, "i=%d\n", i);
        //        fprintf(outfile, "j=%d\n", j);
        //        fprintf(outfile, "k=%d\n", k);
    }
    Path *curr = path_create();
    Path *shortest = path_create();
    dfs(G, START_VERTEX, curr, shortest, cities, outfile);
    printf("Path length: %" PRIu32 "\n", path_length(shortest));
    printf("Path: ");
    path_print(shortest, outfile, cities);
    printf("\n");
    printf("Total recursive calls: %" PRIu32, calls);
    return 0;
}
