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
    uint32_t x;
    stack_peek(p->vertices, &x);
    if (stack_push(p->vertices, v)) {
        p->length += graph_edge_weight(G, x, v);
        return true;
    }
    return false;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x;
    stack_peek(p->vertices, &x);
    if (stack_pop(p->vertices, v)) {
        p->length -= graph_edge_weight(G, x, *v);
        return true;
    }
    return false;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    if (dst) {
        dst->vertices = src->vertices;
        dst->length = src->length;
    }
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, outfile, cities);
}

//int main(void) {
//    char *cities[] = { "Asgard", "Elysium", "Olympus", "Shangri-La" };
//    Path *p = path_create();
//    Graph *G = graph_create(4, false);
//   graph_add_edge(G, 0, 3, 5);
//    graph_add_edge(G, 3, 2, 4);
//   graph_add_edge(G, 2, 1, 10);
//    graph_add_edge(G, 1, 0, 2);
//    graph_print(G);
//    path_push_vertex(p, 0, G);
//    path_push_vertex(p, 3, G);
//    path_push_vertex(p, 2, G);
//    path_push_vertex(p, 1, G);
//    path_push_vertex(p, 0, G);
//    printf("path length: "
//           "%" PRIu32 "\n",
//        path_length(p));
//    printf("path vertices: "
//           "%" PRIu32 "\n",
//        path_vertices(p));
//    printf("graph vertices: "
//           "%" PRIu32 "\n",
//        graph_vertices(G));
//    path_print(p, stdout, cities);
//    return 0;
//}
