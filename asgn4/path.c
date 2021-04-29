#include "path.h"

#include "stack.h"
#include "vertices.h"

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
    }
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
    uint32_t y;
    uint32_t *x = &y;
    if (stack_push(p->vertices, v)) {
        p->length += G->matrix[stack_peek(p->vertices, x)][v];
        return true;
    }
    return false;
}

bool path_pop_vertex(Path *p, *v, Graph *G) {
    uint32_t y;
    uint32_t *x = &y;
    if (stack_pop(p->vertices, v)) {
        p->length -= G->matrix[stack + peek(p->vertices, x)][v];
    }
    return false;
}

uint32_t path_vertices(Path *p) {
    return p->stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    if (dst) {
        dst->vertices = src->vertices;
        dst->length - src->length;
    }
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p_vertices, outfile, cities);
}
