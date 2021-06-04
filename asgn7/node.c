// Darren Lee
// CSE13S
// This program impements the node ADT.

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringdup(char *source) {
    char *copy = (char *) malloc(strlen(source) + 1);
    if (!copy) {
        return NULL;
    }
    strncpy(copy, source, strlen(source) + 1);
    return copy;
}

Node *node_create(char *oldspeak, char *newspeak) {
    // allocate memory for the node
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) { // if the allocation succeeds
        if (oldspeak) {
            n->oldspeak = stringdup(oldspeak);
        } else {
            n->oldspeak = NULL;
        }
        if (newspeak) {
            n->newspeak = stringdup(newspeak);
        } else {
            n->newspeak = NULL;
        }
        n->next = NULL;
        n->prev = NULL;
        return n; // return the node
    } else { // if the allocation fails
        return NULL; // set the pointer to null
    }
}

void node_delete(Node **n) {
    if (*n) {
        if ((*n)->oldspeak) {
            free((*n)->oldspeak);
            (*n)->oldspeak = NULL;
        }
        if ((*n)->newspeak) {
            free((*n)->newspeak);
            (*n)->newspeak = NULL;
        }
        free(*n); // free the memory for n
        *n = NULL; // set the pointer to null
    }
}

// print function provided by Professor Long in assignment pdf
void node_print(Node *n) {
    if (n) {
        if (n->oldspeak && n->newspeak) {
            printf("%s -> %s\n", n->oldspeak, n->newspeak);
        } else if (n->oldspeak) {
            printf("%s\n", n->oldspeak);
        }
    }
}
