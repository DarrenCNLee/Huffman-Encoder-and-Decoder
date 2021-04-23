#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <stdlib.h>

uint32_t q_stack_moves = 0, q_stack_compares = 0;

void q_stack_compares_counter(uint32_t *A, int64_t x, uint32_t p) {
    if (A[x] < p || A[x] > p) {
        q_stack_compares++;
    }
    return;
}

// Python pseudocode for partition function provided by Professor Long in assignment pdf, also influenced by Eugene's lab section on 4/22
static int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1, temp;
    int64_t j = hi + 1;
    do {
        i += 1;
        q_stack_compares_counter(A, i, pivot);
        while (A[i] < pivot) {
            q_stack_compares_counter(A, i, pivot);
            i += 1;
        }
        j -= 1;
        q_stack_compares_counter(A, i, pivot);
        while (A[j] > pivot) {
            q_stack_compares_counter(A, i, pivot);
            j -= 1;
        }
        if (i < j) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            q_stack_moves += 3;
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
    Stack *s = stack_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    while (!stack_empty(s)) {
        stack_pop(s, p_hi);
        stack_pop(s, p_lo);
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            q_stack_compares++;
            stack_push(s, lo);
            stack_push(s, p);
        }
        q_stack_compares++;
        if (hi > p + 1) {
            q_stack_compares++;
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
    }
    return;
}
