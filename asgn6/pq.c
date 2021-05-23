// Darren Lee
// CSE13S
// This program implements the priority queue ADT.

#include "pq.h"

#include "node.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// The priority queue struct has a head, tail, slot, size, capacity, and elements array of nodes.
struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t slot;
    uint32_t size;
    uint32_t capacity;
    Node **elements;
};

// helper function that returns the index to the left in the circular priority queue
uint32_t get_left(PriorityQueue *q, uint32_t i) {
    return (i - 1 + q->capacity) % q->capacity;
}

// helper function that returns the index to the right in the circular priority queue
uint32_t get_right(PriorityQueue *q, uint32_t i) {
    return (i + 1) % q->capacity;
}

PriorityQueue *pq_create(uint32_t capacity) {
    // allocate memory for the priority queue
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) { // if the allocation succeeds
        q->capacity = capacity; // set the capacity
        q->head = 0; // initialize head to 0
        q->tail = 0; // initialize tail to 0
        q->slot = 0; // code inspired by Eugene's lab section on 5/11
        q->size = 0; // initialize size to 0
        // alocate memory for the elements
        q->elements = (Node **) calloc(capacity, sizeof(Node *));
        if (!q->elements) { // if memory allocation fails
            free(q); // free the memory for the priority queue
            q = NULL; // set the pointer to null
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    free((*q)->elements); // free the elements
    free(*q); // free the priority queue
    *q = NULL; // set the pointer to null
}

bool pq_empty(PriorityQueue *q) {
    return !q->size; // if size is 0, the queue is empty
}

bool pq_full(PriorityQueue *q) {
    return q->size == q->capacity; // if size equals capacity, the queue is full
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false; // return false if the queue is full
    }
    // code influenced by Eugene's lab section on 5/11
    q->slot = q->tail; // set slot equal to tail
    // give higher priority to 0 and 255 because we increment their counts in the histogram
    if (n->symbol == 0 || n->symbol == 255) {
        n->frequency--;
    }
    // while the slot!=head and the element to the left of the slot has a higher frequency than the element at the slot or the frequencies are equal and the element to the left has a greater symbol
    while (q->slot != q->head
           && (q->elements[get_left(q, q->slot)]->frequency > n->frequency
               || (q->elements[get_left(q, q->slot)]->frequency == n->frequency
                   && q->elements[get_left(q, q->slot)]->symbol > n->symbol))) {
        // copy the element to the left of the slot to the element at the slot
        q->elements[q->slot] = q->elements[get_left(q, q->slot)];
        q->slot = get_left(q, q->slot); // move the slot to the left
    }
    q->elements[q->slot] = n; // set the element at the slot to n
    q->tail = get_right(q, q->tail); // move the tail to the right
    q->size++; // increment the size
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false; // if the queue is empty, return false
    }
    *n = q->elements[q->head]; // set the node equal to the element at the head
    q->head = get_right(q, q->head); // move the head to the right
    q->size--; // decrement the size
    return true;
}

void pq_print(PriorityQueue *q) {
    if (!pq_full(q)) {
        // print from head to tail if the queue is not full
        for (uint32_t i = q->head; i < q->tail; i++) {
            node_print(q->elements[i]); // print the nodes in the slot elements array
        }
    } else {
        // else print from the head to the left of the tail
        for (uint32_t i = q->head; i <= get_left(q, q->tail); i++) {
            node_print(q->elements[i]);
        }
    }
}
