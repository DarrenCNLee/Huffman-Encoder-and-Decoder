// Darren Lee
// CSE13S
// This program impements the node ADT.

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    // allocate memory for the node
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) { // if the allocation succeeds
        n->symbol = symbol; // set the symbol to symbol
        n->frequency = frequency; // set the frequency to frequency
        n->left = NULL; // set the left child to null
        n->right = NULL; // set the right child to null
        return n; // return the node
    } else { // if the allocation fails
        free(n); // free the memory for n
        return NULL; // set the pointer to null
    }
}

void node_delete(Node **n) {
    free(*n); // free the memory for n
    *n = NULL; // set the pointer to null
}

Node *node_join(Node *left, Node *right) {
    // create a node with symbol '$' and frequency that is the sum of the left and right children's frequencies
    Node *n = node_create('$', left->frequency + right->frequency);
    n->left = left; // set the left child to left
    n->right = right; // set the right child to right
    return n;
}

void node_print(Node *n) {
    printf("Symbol: %c\n", n->symbol); // print the symbol
    printf("Frequency: %" PRIu64 "\n", n->frequency); // print the frequency
}
