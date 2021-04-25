// Darren Lee
// CSE13S Spring 2021
// This program implements two Quick Sorts.
// One uses a stack ADT and the other uses
// a queue ADT.

#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <stdlib.h>

uint32_t max_queue_size, max_stack_size;

// comparison function inspired by Eugene's lab section on 4/22
bool q_less_than_counter(uint32_t *A, int64_t x, uint32_t p) {
    q_compares++;
    return A[x] < p;
}

// comparison function inspired by Eugene's lab section on 4/22
bool q_greater_than_counter(uint32_t *A, int64_t x, uint32_t p) {
    q_compares++;
    return A[x] > p;
}

// Python pseudocode for partition function provided by Professor Long in assignment pdf, also influenced by Eugene's lab section on 4/22
static int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1, j = hi + 1;
    uint32_t temp;
    do {
        i += 1;
        while (q_less_than_counter(A, i, pivot)) {
            i += 1;
        }
        j -= 1;
        while (q_greater_than_counter(A, j, pivot)) {
            j -= 1;
        }
        if (i < j) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            q_moves += 3;
        }
    } while (i < j);
    return j;
}

// Python pseudocode provided by Professor Long in assignment pdf
void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    int64_t *p_hi = &hi;
    int64_t *p_lo = &lo;
    Stack *s = stack_create(2 * n);
    stack_push(s, lo);
    stack_push(s, hi);
    while (!stack_empty(s)) {
        stack_pop(s, p_hi);
        stack_pop(s, p_lo);
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
        if (hi > p + 1) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
        if (stack_size(s) > max_stack_size) {
            max_stack_size = stack_size(s);
        }
    }
    stack_delete(&s);
    return;
}

// Python pseudocode provided by Professor Long in assignment pdf
void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    int64_t *p_hi = &hi;
    int64_t *p_lo = &lo;
    Queue *q = queue_create(2 * n);
    enqueue(q, lo);
    enqueue(q, hi);
    while (!queue_empty(q)) {
        dequeue(q, p_lo);
        dequeue(q, p_hi);
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            enqueue(q, lo);
            enqueue(q, p);
        }
        if (hi > p + 1) {
            enqueue(q, p + 1);
            enqueue(q, hi);
        }
        if (queue_size(q) > max_queue_size) {
            max_queue_size = queue_size(q);
        }
    }
    queue_delete(&q);
    return;
}
