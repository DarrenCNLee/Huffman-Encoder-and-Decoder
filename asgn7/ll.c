#include "ll.h"

#include "node.h"

#include <stdio.h>
#include <stdlib.h>

// struct definition provided by Professor Long in assignment pdf
struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->mtf = mtf;
        ll->length = 0;
        return ll;
    } else {
        return NULL;
    }
}

void ll_delete(LinkedList **ll) {
    for (uint32_t i = 0; i < (*ll)->length; i++) {
        node_delete(&(*ll)->head->next);
        (*ll)->head->next = (*ll)->head->next->next;
        (*ll)->head->next->next->prev = (*ll)->head;
    }
    free(*ll);
    *ll = NULL;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    Node *curr = ll->head;
    for (uint32_t i = 0; i < ll->length; i++) {
        curr = curr->next;
        if (curr->oldspeak == oldspeak) {
            if (ll->mtf) {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr->next = ll->head->next;
                curr->prev = ll->head;
                ll->head->next->prev = curr;
                ll->head->next = curr;
                return curr;
            }
        }
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (!ll_lookup(ll, oldspeak)) {
        Node *n = node_create(oldspeak, newspeak);
        ll->head->next->prev = n;
        n->next = ll->head->next;
        n->prev = ll->head;
        ll->head->next = n;
        ll->length++;
    }
}

void ll_print(LinkedList *ll) {
    Node *curr = ll->head;
    for (uint32_t i = 0; i < ll->length; i++) {
        curr = curr->next;
        node_print(curr);
    }
}
