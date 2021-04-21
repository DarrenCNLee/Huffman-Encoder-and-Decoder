#include "quick.h"

#include <math.h>
#include <stdlib.h>

int64_t partition(uint32_t *A, lo, hi) {
    int pivot = A[lo + floor((hi - lo), 2)];
    int i = lo - 1, temp;
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
        i++;
    } while (i < j);
    return j;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    //	stack_create(n);
    //	stack_push(lo)
    return;
}
