#include "pq.h"

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t slot;
    uint32_t size;
    uint32_t capacity;
    Node **elements;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->head = 0;
        q->tail = 0;
        q->slot = 0; // code inspired by Eugene's lab section on 5/11
        q->size = 0;
        q->elements = (Node **) calloc(capacity, sizeof(Node *));
        if (!q->elements) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    free((*q)->elements);
    free(*q);
    *q = NULL;
}

bool pq_empty(PriorityQueue *q) {
    return !q->size;
}

bool pq_full(PriorityQueue *q) {
    return q->size == q->capacity;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    // code influenced by Eugene's lab section on 5/11
    q->slot = q->tail;
    while ((q->slot != q->head)
           && (q->elements[(q->slot - 1 + q->capacity) % q->capacity]->frequency > n->frequency)) {
        q->elements[q->slot] = q->elements[(q->slot - 1 + q->capacity) % q->capacity];
        q->slot--;
    }
    while ((q->slot != q->head)
           && (q->elements[(q->slot - 1 + q->capacity) % q->capacity]->frequency == n->frequency)
           && (q->elements[(q->slot - 1 + q->capacity) % q->capacity]->symbol > n->symbol)) {
        q->elements[q->slot] = q->elements[(q->slot - 1 + q->capacity) % q->capacity];
        q->slot--;
    }
    q->elements[q->slot] = n;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    *n = q->elements[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return true;
}

void pq_print(PriorityQueue *q) {
    if (!pq_full(q)) {
        for (uint32_t i = q->head; i < q->tail; i++) {
            node_print(q->elements[i]);
        }
    } else {
        for (uint32_t i = q->head; i <= (q->tail - 1 + q->capacity) % q->capacity; i++) {
            node_print(q->elements[i]);
        }
    }
}
