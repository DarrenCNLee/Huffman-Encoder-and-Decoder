#include "bubble.h"

uint32_t b_moves = 0, b_compares = 0;

// Pseudocode provided by Professor Long in assignment pdf
void bubble_sort(uint32_t *A, uint32_t n) {
    int swapped = 1, temp;
    while (swapped) {
        swapped = 0;
        for (uint32_t i = 1; i < n; i++) {
            b_compares += 1;
            if (A[i] < A[i - 1]) {
                temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                swapped = 1;
                b_moves += 3;
            }
        }
        n -= 1;
    }
}
