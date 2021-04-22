#include "shell.h"

#include "gaps.h"

uint32_t s_moves = 0,
         s_compares = 0; // s_moves is number of moves, s_compares is number of compares

// Pseudocode in Python provided by Professor Long in assignment pdf
void shell_sort(uint32_t *A, uint32_t n) {
    uint32_t j, temp;
    for (uint32_t k = 0; k < sizeof(gaps) / sizeof(uint32_t); k++) {
        for (uint32_t i = gaps[k]; i < n; i++) {
            j = i;
            s_compares++;
            temp = A[i];
            while (j >= gaps[k] && temp < A[j - gaps[k]]) {
                A[j] = A[j - gaps[k]];
                j -= gaps[k];
                s_compares++;
                s_moves++;
            }
            A[j] = temp;
            s_moves += 2;
        }
    }
}
