#include "shell.h"

#include "gaps.h"

uint32_t s_moves, s_compares; // s_moves is number of moves, s_compares is number of compares

void shell_sort(uint32_t *A, uint32_t n) { // Pseudocode in Python provided by assignment pdf
    uint32_t j, temp;
    for (uint32_t k = 0; k < sizeof(gaps) / 4; k++) {
        for (uint32_t i = gaps[k]; i < n; i++) {
            s_compares += 1;
            j = i;
            temp = A[i];
            while (j >= gaps[k] && temp < A[j - gaps[k]]) {
                A[j] = A[j - gaps[k]];
                j -= gaps[k];
            }
            A[j] = temp;
            s_moves += 2;
        }
    }
}
