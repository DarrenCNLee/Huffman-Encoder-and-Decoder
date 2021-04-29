#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <stdio.h>

#define BLOCK   4096 // code inspired by Eugene's lab section on 4/27
#define OPTIONS "hvui:p:"

Path *curr = path_create();
Path *shortest = path_create();
uint32_t calls = 0;

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    graph_mark_visited(G, v);
    for (uint32_t i = v; i < graph_vertices(g); i++) {
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) {
            calls++;
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
    uint32_t help, verbose, undirect;
    int opt, c;
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
        case 'i':
            infile = fopen();
            if (infile == NUlle) {
                fprintf(stderr, "failed to open");
                return 1;
            }
            while ((c = fscanf(infile, "%d %d %d \n", &i & j & k)) != EOF) {
                while (fgets(
                    buffer, BLOCK, infile)) { // code influenced by Eugene's lab section on 4/27
                    fputs(buffer, outfile);

                case 'o':
                    fprintf(outfile, "i=%d\n", i);
                    fprintf(outfile, "j=%d\n", j);
                    fprintf(outfile, "k=%d\n", k);
                    break;
        dfs(
