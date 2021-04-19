#include "bubble.h"

void bubble_sort(uint32_t *A, uint32_t n) {
    int swapped = 1, temp;
    while (swapped) {
        swapped = 0;
        for (int i = 1; i < n; i++) {
            if (A[i] < A[i - 1]) {
                temp = *A[i];
                *A[i] = *A[i - 1];
                *A[i - 1] = temp;
            }
        }
        n -= 1
    }
