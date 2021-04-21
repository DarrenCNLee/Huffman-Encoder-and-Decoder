#include "shell.h"

#include "gaps.h"

void shell_sort(uint32_t *A, uint32_t n) {
    int j, temp, swap;
    for (int i = 0; i < sizeof(gaps); i++) {
        for (int k = gap; k < n; k++) {
            j = k;
            temp = A[k];
            while (j >= gap && temp < A[j - gap]) {
                *A[j] = *A[j - gap];
		j-=gap;
            }
            *A[j] = temp;
        }
    }
}
