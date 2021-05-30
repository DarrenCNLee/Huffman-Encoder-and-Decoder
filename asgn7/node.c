// Darren Lee
// CSE13S
// This program impements the node ADT.

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringdup(char *source) {
    char *copy = malloc(strlen(source) + 1);
    if (!copy) {
        return NULL;
    }
    strcpy(copy, source);
    return copy;
}

Node *node_create(char *oldspeak, char *newspeak) {
    // allocate memory for the node
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) { // if the allocation succeeds
        n->oldspeak = stringdup(oldspeak);
        n->newspeak = stringdup(newspeak);
        return n; // return the node
    } else { // if the allocation fails
        return NULL; // set the pointer to null
    }
}

void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n); // free the memory for n
    *n = NULL; // set the pointer to null
}

// print function provided by Professor Long in assignment pdf
void node_print(Node *n) {
    printf("%s -> %s\n", n->oldspeak, n->newspeak);
    printf("%s\n", n->oldspeak);
}
