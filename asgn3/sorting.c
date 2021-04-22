#include "bubble.h"
#include "quick.h"
#include "set.h" // set code provided by Eugene on Piazza
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
    return;
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
    return;
}

void print_quick_stack(uint32_t *A, uint32_t n, uint32_t p) {
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
    return;
}

void print_quick_queue(uint32_t *A, uint32_t n, uint32_t p) {
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
    return;
}

int main(int argc, char **argv) {
    enum opts { b, s, q, Q };
    Set opt_set = set_empty();
    int opt = 0;
    uint32_t seed = 13371453;
    int64_t size = 100, elem = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            opt_set = set_insert(opt_set, b);
            opt_set = set_insert(opt_set, s);
            opt_set = set_insert(opt_set, q);
            opt_set = set_insert(opt_set, Q);
            break;
        case 'b': opt_set = set_insert(opt_set, b); break;
        case 's': opt_set = set_insert(opt_set, s); break;
        case 'q': opt_set = set_insert(opt_set, q); break;
        case 'Q': opt_set = set_insert(opt_set, Q); break;
        case 'r': seed = strtol(optarg, NULL, 10); break;
        case 'n': size = strtol(optarg, NULL, 10); break;
        case 'p': elem = strtol(optarg, NULL, 10); break;
        }
    }
    uint32_t arr[size];
    if (set_member(opt_set, b)) {
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        print_bubble(arr, size, elem);
    }
    if (set_member(opt_set, s)) {
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        print_shell(arr, size, elem);
    }
    if (set_member(opt_set, q)) {
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        //		print_quick_stack();
    }
    if (set_member(opt_set, Q)) {
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        //		print_quick_queue();
    }
    return 0;
}
