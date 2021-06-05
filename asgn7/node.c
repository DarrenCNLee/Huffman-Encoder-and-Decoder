// Darren Lee
// CSE13S
// This program implements the node ADT.

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringdup(char *source) {
    // create a copy with 1 extra byte for the null terminator
    char *copy = (char *) malloc(strlen(source) + 1);
    if (!copy) { // return null if memory allocation fails
        return NULL;
    }
    // copy the source to the new copy
    strncpy(copy, source, strlen(source) + 1);
    return copy;
}

Node *node_create(char *oldspeak, char *newspeak) {
    // allocate memory for the node
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) { // if the allocation succeeds
        if (oldspeak) { // duplicate oldspeak if oldspeak is not null
            n->oldspeak = stringdup(oldspeak);
        } else { // else set it to null
            n->oldspeak = NULL;
        }
        if (newspeak) { // duplicate newspeak if newspeak is not null
            n->newspeak = stringdup(newspeak);
        } else { // else set it to null
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
        if ((*n)->oldspeak) { // free oldspeak and set pointer to null
            free((*n)->oldspeak);
            (*n)->oldspeak = NULL;
        }
        if ((*n)->newspeak) { // free newspeak and set pointer to null
            free((*n)->newspeak);
            (*n)->newspeak = NULL;
        }
        free(*n); // free the memory for n
        *n = NULL; // set the pointer to null
    }
}

// print function provided by Professor Long in assignment pdf
void node_print(Node *n) {
    if (n->oldspeak && n->newspeak) {
        // if the node has oldspeak and newspeak, print both
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else if (n->oldspeak) {
        // else if the node only has oldspeak, print the oldspeak
        printf("%s\n", n->oldspeak);
    }
}
