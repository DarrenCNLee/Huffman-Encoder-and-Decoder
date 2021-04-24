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
    return q->tail - q->head;
}

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
/*
int main(void) {
    int64_t y;
    int64_t *x = &y;
    Queue *q = queue_create(5);
    printf("queue full? %d\n", queue_full(q));
    enqueue(q, 13);
    enqueue(q, 1);
    enqueue(q, 1);
    enqueue(q, 50);
    queue_print(q);
    printf("queue full? %d\n", queue_full(q));
    dequeue(q, x);
    dequeue(q, x);
    dequeue(q, x);
    dequeue(q, x);
    dequeue(q, x);
    dequeue(q, x);
    printf("x=%" PRId64 "\n", *x);
    queue_print(q);
    printf("queue empty? %d\n", queue_empty(q));
    enqueue(q, 11);
    enqueue(q, 13);
    enqueue(q, 13);
    enqueue(q, 20);
    queue_print(q);
    printf("queue full? %d\n", queue_full(q));
    printf("queue empty? %d\n", queue_empty(q));
    dequeue(q, x);
    dequeue(q, x);
    dequeue(q, x);
    dequeue(q, x);
    dequeue(q, x);
    printf("x=%" PRId64 "\n", *x);
    queue_print(q);
    printf("queue empty? %d\n", queue_empty(q));
}*/
