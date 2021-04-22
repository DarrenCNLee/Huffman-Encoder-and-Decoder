#include "bubble.h"
#include "quick.h"
#include "shell.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"

extern uint32_t b_moves, b_compares, s_moves, s_compares;

void print_bubble(uint32_t *A, uint32_t n, uint32_t p) {
    bubble_sort(A, n);
    printf("Bubble Sort\n");
    printf(
        "%" PRIu32 " elements, %" PRIu32 " moves, %" PRIu32 " compares\n", n, b_moves, b_compares);
    uint32_t i = 0;
    while (i < p && i < n) {
        for (int j = 0; j < 5; j++) {
            printf("%13" PRIu32, A[i]);
            i++;
            if (i >= p || i >= n) {
                break;
            }
        }
        printf("\n");
    }
}

void print_shell(uint32_t *A, uint32_t n, uint32_t p) {
    shell_sort(A, n);
    printf("Shell Sort\n");
    printf(
        "%" PRIu32 " elements, %" PRIu32 " moves, %" PRIu32 " compares\n", n, s_moves, s_compares);
    uint32_t i = 0;
    while (i < p && i < n) {
        for (int j = 0; j < 5; j++) {
            printf("%13" PRIu32, A[i]);
            i++;
            if (i >= p || i >= n) {
                break;
            }
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t seed = 13371453;
    int64_t size = 100, elem = 100;
    int bubble = 0, shell = 0, quick_stack = 0, quick_queue = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            if (!bubble) {
                bubble = 1;
            }
            if (!shell) {
                shell = 1;
            }
            if (!quick_stack) {
                quick_stack = 1;
            }
            if (!quick_queue) {
                quick_queue = 1;
            }
            break;
        case 'b':
            if (!bubble) {
                bubble = 1;
            }
            break;
        case 's':
            if (!shell) {
                shell = 1;
            }
            break;
        case 'q':
            if (!quick_stack) {
                quick_stack = 1;
            }
            break;
        case 'Q':
            if (!quick_queue) {
                quick_queue = 1;
            }
            break;
        case 'r': seed = strtol(optarg, NULL, 10); break;
        case 'n': size = strtol(optarg, NULL, 10); break;
        case 'p': elem = strtol(optarg, NULL, 10); break;
        }
    }
    srandom(seed);
    uint32_t arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = random();
    }
    if (bubble) {
        print_bubble(arr, size, elem);
    }
    if (shell) {
        print_shell(arr, size, elem);
    }
    if (quick_stack) {
        //		print_quick_stack();
    }
    if (quick_queue) {
        //		print_quick_queue();
    }
    return 0;
}
