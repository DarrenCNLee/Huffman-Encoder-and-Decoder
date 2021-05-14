#include "pq.h"

#include <stdio.h>
#include <stdlib.h>

struct Queue {
    uint32_t head;
    uint32_t tail;
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
        q->size = 0;
        q->elements = (Node *) calloc(capacity, sizeof(Node));
        if (!q->elements) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    free((*q)->items);
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
    if pq_full (q) {
        return false;
    }
    q->elements[q->tail] = n;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if pq_empty (q) {
        return false;
        *n = q->elements[q->head];
        q->head = (q->head + 1) % q->capacity;
        q->size--;
        return true;
    }

    void pq_print(PriorityQueue * q) {
        for (uint32_t i = q->head; i < q->tail; q++) {
            printf(q->elements[i]);
        }
        printf("\n");
    }
