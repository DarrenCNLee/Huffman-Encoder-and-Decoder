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
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
        if (stack_empty(p->vertices)) {
            free(p);
            p = NULL;
        }
    }
    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x;
    if (stack_full(p->vertices)) {
        return false;
    }
    stack_peek(p->vertices, &x);
    stack_push(p->vertices, v);
    p->length += graph_edge_weight(G, x, v);
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x;
    if (stack_empty(p->vertices)) {
        return false;
    }
    stack_pop(p->vertices, v);
    stack_peek(p->vertices, &x);
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

//int main(void) {
//    uint32_t x;
//    Graph *G = graph_create(4, false);
//    Path *p = path_create();
//    char *cities[4] = { "Asgard", "Elysium", "Olympus", "Shangri-La" };
//    graph_add_edge(G, 0, 3, 5);
//    graph_add_edge(G, 3, 2, 4);
//    graph_add_edge(G, 2, 1, 10);
//    graph_add_edge(G, 1, 0, 2);
//    path_push_vertex(p, 0, G);
//    path_push_vertex(p, 3, G);
//    path_push_vertex(p, 2, G);
//    path_push_vertex(p, 1, G);
//    path_push_vertex(p, 0, G);
//    path_print(p, stdout, cities);
//    printf("path length: %" PRIu32 "\n", path_length(p));
//    path_pop_vertex(p, &x, G);
//    printf("x = %" PRIu32 "\n", x);
//    path_print(p, stdout, cities);
//    printf("path length: %" PRIu32 "\n", path_length(p));
//    return 0;
//}
