// Darren Lee
// CSE13S Spring 2021
// This program implements the path ADT functions.

#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdlib.h>

// code for path struct provided by Professor Long in assignment pdf
struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES + 1); // initialize the vertices
        p->length = 0; // initialize the length
    }
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices); // delete the vertices stack
        free((*p)->vertices);
        free(*p);
        *p = NULL; // set the pointer to null
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (stack_full(p->vertices)) { // return false if the vertices stack is full
        return false;
    }
    if (stack_size(p->vertices) > 0) {
        uint32_t x;
        stack_peek(p->vertices, &x);
        stack_push(p->vertices, v);
        if (v != x) {
            p->length += graph_edge_weight(
                G, x, v); // add the weight from the last vertex to the pushed vertex
        }
    } else if (stack_size(p->vertices) == 0) {
        stack_push(p->vertices, v);
    }
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) { // return false if the vertices stack is empty
        return false;
    }
    if (stack_size(p->vertices) > 1) {
        uint32_t x;
        stack_pop(p->vertices, v);
        stack_peek(p->vertices, &x);
        if (*v != x) {
            p->length -= graph_edge_weight(
                G, x, *v); // subtract the weight from the last vertex to the popped vertex
        }
    } else if (stack_size(p->vertices) == 1) {
        stack_pop(p->vertices, v);
    }
    return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    if (dst) {
        stack_copy(dst->vertices,
            src->vertices); // copy the vertices stack from the source to the destination
        dst->length = src->length; // set the length of the destination to the length of the source
    }
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
