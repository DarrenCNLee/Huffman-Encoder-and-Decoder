#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <math.h>
#include <stdlib.h>

int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1, temp;
    int64_t j = hi + 1;
    do {
        while (A[i] < pivot) {
            i += 1;
        }
        j -= 1;
        while (A[j] > pivot) {
            j -= 1;
        }
        if (i < j) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    } while (i < j);
    return j;
}

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
            stack_push(s, lo);
            stack_push(s, p);
        }
        if (hi > p + 1) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
    }
    return;
}
