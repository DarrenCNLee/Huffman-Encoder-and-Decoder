// Darren Lee
// CSE13S Spring 2021
// This program implements the graph ADT and its functions.

#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// code for graph struct provided by Professor Long in assignment pdf
struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    G->undirected = undirected; // initialize undirected value
    G->vertices = vertices; // initialize vertices
    if (!G->vertices) {
        free(G);
        G = NULL;
    }
    for (uint32_t i = 0; i < vertices; i++) {
        G->visited[i] = false; // initialize all vertices to be unvisited
        for (uint32_t j = 0; j < vertices; j++) {
            G->matrix[i][j] = 0; // initialize all edge weights to 0
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    if (*G && (*G)->vertices) {
        free(*G); // free the memory for the graph
        *G = NULL; // set the pointer to 0
    }
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (!(i < G->vertices) || !(j < G->vertices)) {
        return false; // return false if either of the vertices is out of bounds
    }
    G->matrix[i][j] = k; // set the edge weight from i to j to be k
    if (G->undirected) { // mirror the weight from j to  i if the graph is undirected
        G->matrix[j][i] = k;
    }
    return true;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i < G->vertices && j < G->vertices) {
        return G->matrix[i][j]; // return true if there is a non-zero edge weight
    }
    return false; // return false if either of the vertices is out of bounds
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if ((i >= G->vertices) || (j >= G->vertices)) {
        return 0; // return 0 if either of the edge weights is out of bounds
    }
    return G->matrix[i][j]; // return edge weight
}

bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v < G->vertices) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
        for (uint32_t j = 0; j < G->vertices; j++) {
            if (G->matrix[i][j]) {
                printf("%" PRIu32 " "
                       "%" PRIu32 " "
                       "%" PRIu32 "\n",
                    i, j, G->matrix[i][j]);
            }
        }
    }
}
