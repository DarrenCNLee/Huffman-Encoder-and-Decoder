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

//            if (path_length(curr) > path_length(shortest)) {
//                continue;
//            }
//    path_pop_vertex(curr, &v, G);

// pseudocode for dfs given by Professor Long in assignment pdf
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    uint32_t x;
    calls++;
    graph_mark_visited(G, v);
    for (uint32_t w = 0; w < graph_vertices(G); w++) {
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) {
            path_push_vertex(curr, w, G);
            dfs(G, w, curr, shortest, cities, outfile);
            path_pop_vertex(curr, &x, G);
        }
        if ((path_vertices(curr) == graph_vertices(G) - 1) && (graph_has_edge(G, v, START_VERTEX))
            && ((path_length(shortest) == 0) || (path_length(curr) < path_length(shortest)))) {
            path_push_vertex(curr, START_VERTEX, G);
            path_copy(shortest, curr);
            path_pop_vertex(curr, &x, G);
        }
    }
    graph_mark_unvisited(G, v);
}

int main(int argc, char **argv) {
    char buffer[BLOCK]; // code influenced by Eugene's lab section on 4/27
    FILE *infile = stdin, *outfile = stdout;
    uint32_t help = 0, verbose = 0, undirect = 0;
    int opt, c, i, j, k, n;
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
        fprintf(stderr, "Failed to open infile\n");
        return 1;
    }
    if (outfile == NULL) {
        fprintf(stderr, "Failed to open outfile\n");
        return 1;
    }
    fscanf(infile, "%d", &n);
    if (n > VERTICES) {
        fprintf(stderr, "Too many vertices\n");
        fclose(infile);
        return 1;
    }
    if (n <= 0) {
        fprintf(stderr, "There's nowhere to go.\n");
        fclose(infile);
        return 1;
    }
    char *cities[n];
    fgets(buffer, BLOCK, infile); // code influenced by Eugene's lab section on 4/27
    for (int i = 0, j = 1; j <= n; i++, j++) {
        fgets(buffer, BLOCK, infile); // code influenced by Eugene's lab section on 4/27
        strtok(buffer, "\n");
        cities[i] = strdup(buffer);
    }
    Graph *G = graph_create(n, undirect);
    // code influenced by Eugene's lab section on 4/27
    while ((c = fscanf(infile, "%d %d %d \n", &i, &j, &k)) != EOF) {
        if (c != 3) { // code influenced by Eugene's lab section on 4/27
            fprintf(stderr, "Error: malformed edge.\n");
            fclose(infile);
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
    if (path_length(shortest) == 0) {
        fprintf(stderr, "There's nowhere to go.\n");
        fclose(infile);
        for (int i = 0; i < n; i++) { // code influenced by Eugene's lab section on 4/27
            free(cities[i]);
        }
        path_delete(&curr);
        path_delete(&shortest);
        graph_delete(&G);
        return 1;
    }
    printf("Path length: %" PRIu32 "\n", path_length(shortest));
    printf("Path: %s -> ", cities[START_VERTEX]);
    path_print(shortest, stdout, cities);
    printf("Total recursive calls: %" PRIu32 "\n", calls);
    for (int i = 0; i < n; i++) { // code influenced by Eugene's lab section on 4/27
        free(cities[i]);
    }
    path_delete(&curr);
    path_delete(&shortest);
    graph_delete(&G);
    return 0;
}
