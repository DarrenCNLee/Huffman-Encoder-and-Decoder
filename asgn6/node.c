#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    free(n);
    return NULL;
}

void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

Node *node_join(Node *left, Node *right) {
    return node_create('$', left->frequency + right->frequency);
}

void node_print(Node *n) {
    printf("Symbol: %c\n", n->symbol);
    printf("Frequency: %" PRIu64, n->frequency);
    printf("\n");
}
