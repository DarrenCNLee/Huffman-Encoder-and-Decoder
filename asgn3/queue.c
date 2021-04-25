// Darren Lee
// CSE13S Spring 2021
// This program implements the queue abstract
// data type used by one of the Quick Sorts.

#include "queue.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// code for Queue structure provided by Professor Long in assignment pdf
struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};

// code influenced by stack constructor code provided by Professor Long in assignment pdf
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        q->size = 0;
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

// code influenced by stack destructor code provided by Professor Long in assignment pdf
void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    return !q->size;
}

bool queue_full(Queue *q) {
    return q->size == q->capacity;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

// code influenced by Eugene's 4/22 lab section
bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q)) {
        return false;
    } else {
        q->items[q->tail] = x;
        q->tail = (q->tail + 1) % q->capacity;
        q->size++;
        return true;
    }
}

// code influenced by Eugene's 4/22 lab section
bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q)) {
        return false;
    } else {
        *x = q->items[q->head];
        q->head = (q->head + 1) % q->capacity;
        q->size--;
        return true;
    }
}

void queue_print(Queue *q) {
    for (uint32_t i = q->head; i < q->tail; i++) {
        printf("% " PRId64, q->items[i]);
    }
    printf("\n");
    return;
}
