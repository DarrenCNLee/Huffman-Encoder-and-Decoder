#include "graph.h"

#include "vertices.h"

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(Sizeof(*Graph));
    if (G) {
        G->undirected = undirected;
        G->vertices = (uint32_t *) calloc(vertices, sizeof(uint32_t));
        if (!G->vertices) {
            free(G);
            G = NULL;
        }
        for (uint32_t i = 0; i < G->vertices; i++) {
            G->visited[i] = false;
            for (uint32_t j = 0; j < G->vertices; j++) {
                G->matrix[i][j] = 0;
            }
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    if (*G && (*G)->vertices) {
        for (uint32_t i = 0; i < G->vertices; i++) {
            for (uint32_t j = 0; j < G->vertices; j++) {
                free((*G)->matrix[i][j]);
            }
        }
        free((*G)->undirected);
        free((*G)->visited);
        free((*G)->vertices);
        free(*G);
        *G = NULL;
    }
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (!(i < G->vertices) || !(j < G->vertices)) {
        return false;
    }
    G->matrix[i][j] = k;
    if (G->undirected) {
        G->matrix[i][j] = k;
    }
    return true;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (!(i < G->vertices) || !(j < G->vertices) || !G->matrix[i][j]) {
        return 0;
    }
    return G->matrix[i][j];
}

bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            if (G->matrix[i][j]) {
                printf("%" PRIu32 "\n", G->matrix[i][j]);
            }
        }
    }
}
