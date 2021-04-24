// Darren Lee
// CSE13S Spring 2021
// This program implements Shell Sort.

#include "shell.h"

#include "gaps.h"

uint32_t s_moves = 0, s_compares = 0; // counts for moves and comparisons

// Pseudocode in Python provided by Professor Long in assignment pdf
void shell_sort(uint32_t *A, uint32_t n) {
    uint32_t j, temp;
    for (uint32_t k = 0; k < sizeof(gaps) / sizeof(uint32_t); k++) {
        for (uint32_t i = gaps[k]; i < n; i++) {
            j = i;
            temp = A[i];
            s_moves++;
            while (j >= gaps[k] && temp < A[j - gaps[k]]) {
                s_compares++;
                A[j] = A[j - gaps[k]];
                s_moves++;
                j -= gaps[k];
            }
            if (j >= gaps[k]) { // comparison count code influenced by Eugene's 4/22 section
                s_compares++;
            }
            A[j] = temp;
            s_moves++;
        }
    }
    return;
}
