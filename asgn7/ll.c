// Darren Lee
// CSE13S
// This program implements the linked list ADT.

#include "ll.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t seeks, links; // for counting seeks and links

// struct definition provided by Professor Long in assignment pdf
struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    // allocate memory for linked list
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->head = node_create(NULL, NULL); // create head
        ll->tail = node_create(NULL, NULL); // create tail
        ll->head->next = ll->tail; // set head's next to tail
        ll->tail->prev = ll->head; // set tail's prev to head
        ll->mtf = mtf;
        ll->length = 0;
        return ll;
    } else {
        return NULL;
    }
}

void ll_delete(LinkedList **ll) {
    if (*ll) {
        Node *curr = (*ll)->head; // start from the head
        while (curr) { // while cur is not null
            Node *next = curr->next; // save curr's next node
            node_delete(&curr); // delete curr
            curr = next; // set curr to next
        }
        free(*ll); // free the linked list
        *ll = NULL; // set the pointer to null
    }
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    if (ll) {
        seeks++; // increment number of seeks
        Node *curr = ll->head; // start at the head
        for (uint32_t i = 0; i < ll->length; i++) {
            curr = curr->next; // set curr to its next node
            if (!strcmp(curr->oldspeak, oldspeak)) { // if oldspeak matches
                if (ll->mtf) { // if mtf is enabled
                    // move the node to the front of the list
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr->next = ll->head->next;
                    curr->prev = ll->head;
                    ll->head->next->prev = curr;
                    ll->head->next = curr;
                }
                return curr; // return the node
            }
            links++; // increment links
        }
    }
    return NULL; // return null if the node is not found
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (!ll_lookup(ll, oldspeak)) {
        // if the list does not already have a node with oldspeak
        // create a new node with oldspeak and newspeak
        Node *n = node_create(oldspeak, newspeak);
        // insert the node into the linked list at the head
        ll->head->next->prev = n;
        n->next = ll->head->next;
        n->prev = ll->head;
        ll->head->next = n;
        ll->length++; // increment the length
    }
}

void ll_print(LinkedList *ll) {
    Node *curr = ll->head; // start at the head
    for (uint32_t i = 0; i < ll->length; i++) {
        curr = curr->next;
        node_print(curr); // print each node except for the head and tail
    }
}
