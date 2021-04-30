#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    p->vertices = stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        free((*p)->vertices);
        free(*p);
        (*p) = NULL;
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x;
    stack_peek(p->vertices, &x);
    if (stack_full(p->vertices)) {
        return false;
    }
    stack_push(p->vertices, v);
    p->length += graph_edge_weight(G, x, v);
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x;
    stack_peek(p->vertices, &x);
    if (stack_empty(p->vertices)) {
        return false;
    }
    stack_pop(p->vertices, v);
    p->length -= graph_edge_weight(G, x, *v);
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
        stack_copy(dst->vertices, src->vertices);
        dst->length = src->length;
    }
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}
