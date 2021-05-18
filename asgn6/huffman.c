#include "huffman.h"

#include "code.h"
#include "defines.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void postorder(Node *n, Code table[static ALPHABET], Code c) {
    uint8_t bit;
    if (n) {
        code_push_bit(&c, 0);
        postorder(n->left, table, c);
        code_pop_bit(&c, &bit);
        code_push_bit(&c, 1);
        postorder(n->right, table, c);
        code_pop_bit(&c, &bit);
        if (n->left == NULL && n->right == NULL) {
            table[n->symbol] = c;
        }
    }
}

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET);
    Node *left;
    Node *right;
    Node *root;
    Node *n;
    Node *parent;
    hist[0]++;
    hist[255]++;
    n = node_create(0, hist[0]);
    enqueue(q, n);
    n = node_create(255, hist[255]);
    enqueue(q, n);
    dequeue(q, &left);
    dequeue(q, &right);
    parent = node_join(left, right);
    enqueue(q, parent);
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0 && i != 0 && i != 255) {
            n = node_create(i, hist[i]);
            enqueue(q, n);
        }
    }
    while (pq_size(q) > 1) {
        dequeue(q, &left);
        dequeue(q, &right);
        parent = node_join(left, right);
        enqueue(q, parent);
    }
    dequeue(q, &root);
    return root;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();
    postorder(root, table, c);
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *s = stack_create(ALPHABET);
    Node *left;
    Node *right;
    Node *root;
    for (uint16_t i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') {
            Node *n = node_create(tree_dump[i + 1], 0);
            stack_push(s, n);
        }
        if (tree_dump[i] == 'I') {
            stack_pop(s, &right);
            stack_pop(s, &left);
            Node *parent = node_join(left, right);
            stack_push(s, parent);
        }
    }
    stack_pop(s, &root);
    return root;
}

void delete_tree(Node **root) {
    if (*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        free(*root);
    }
    *root = NULL;
}
