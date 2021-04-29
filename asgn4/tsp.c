#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

Path *curr = path_create();
Path *shortest = path_create();

void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile) {
    graph_mark_visited(G, v);
    for (uint32_t i = v; i < graph_vertices(g); i++) {
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
        dfs(
