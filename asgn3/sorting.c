// Darren Lee
// CSE13S Spring 2021
// This program implements the test harness for the
// Bubble Sort, Shell Sort, and two Quick Sorts.

#include "bubble.h"
#include "queue.h"
#include "quick.h"
#include "set.h" // set code provided by Eugene on Piazza
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "absqQr:n:p:"

extern uint32_t b_moves, b_compares, s_moves, s_compares, q_moves, q_compares;

void print_bubble(uint32_t *A, uint32_t n, uint32_t p) {
    b_moves = b_compares = 0;
    bubble_sort(A, n);
    printf("Bubble Sort\n");
    // code for formatting print statement provided by Professor Long in assignment pdf
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
    s_moves = s_compares = 0;
    shell_sort(A, n);
    printf("Shell Sort\n");
    // code for formatting print statement provided by Professor Long in assignment pdf
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
    q_moves = q_compares = 0;
    quick_sort_stack(A, n);
    printf("Quick Sort (Stack)\n");
    // code for formatting print statement provided by Professor Long in assignment pdf
    printf(
        "%" PRIu32 " elements, %" PRIu32 " moves, %" PRIu32 " compares\n", n, q_moves, q_compares);
    printf("Max stack size: %" PRIu32 "\n", max_stack_size);
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
    q_moves = q_compares = 0;
    quick_sort_queue(A, n);
    printf("Quick Sort (Queue)\n");
    // code for formatting print statement provided by Professor Long in assignment pdf
    printf(
        "%" PRIu32 " elements, %" PRIu32 " moves, %" PRIu32 " compares\n", n, q_moves, q_compares);
    printf("Max queue size: %" PRIu32 "\n", max_queue_size);
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
    uint32_t seed = 13371453; // default seed
    int64_t size = 100, elem = 100; // default size and number of elements to print
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': // add all sorts to option set
            opt_set = set_insert(opt_set, b);
            opt_set = set_insert(opt_set, s);
            opt_set = set_insert(opt_set, q);
            opt_set = set_insert(opt_set, Q);
            break;
        case 'b': opt_set = set_insert(opt_set, b); break; // add bubble sort to option set
        case 's': opt_set = set_insert(opt_set, s); break; // add Shell Sort to option set
        case 'q': opt_set = set_insert(opt_set, q); break; // add stack Quick Sort to option set
        case 'Q': opt_set = set_insert(opt_set, Q); break; // add queue Quick Sort to option set
        case 'r': seed = strtoul(optarg, NULL, 10); break;
        case 'n':
            size = strtoul(optarg, NULL, 10);
            if (size == 0) { // handle error when size = 0
                fprintf(stderr, "Invalid array length.\n");
                return 1;
            }
            if (size < 0) { // handle error when size is negative
                fprintf(stderr, "Failed to allocate array to sort.\n");
                return 1;
            }
            break;
        case 'p': elem = strtoul(optarg, NULL, 10); break;
        default: // print usage guide if no valid options are selected
            printf("Select at least one sort to perform.\n");
            printf("SYNOPSIS\n");
            printf("    A collection of comparison-based sorting algorithms.\n");
            printf("\n");
            printf("USAGE\n   ./ sorting [-absqQ] [-n length] [-p elements] [-r seed]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -b              Enable Bubble Sort.\n");
            printf("   -s              Enable Shell Sort.\n");
            printf("   -q              Enable Quick Sort(Stack).\n");
            printf("   -Q              Enable Quick Sort(Queue).\n");
            printf("   -n length       Specify number of array elements.\n");
            printf("   -p elements     Specify number of elements to print.\n");
            printf("   -r seed         Specify random seed.\n");
            return 1;
        }
    }
    uint32_t arr[size];
    if (set_member(opt_set, b)) { // create array for Bubble Sort
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        print_bubble(arr, size, elem);
    }
    if (set_member(opt_set, s)) { // create array for Shell Sort
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        print_shell(arr, size, elem);
    }
    if (set_member(opt_set, q)) { // create array for stack Quick Sort
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        print_quick_stack(arr, size, elem);
    }
    if (set_member(opt_set, Q)) { // create array for queue Quick Sort
        srandom(seed);
        for (int i = 0; i < size; i++) {
            arr[i] = random();
        }
        print_quick_queue(arr, size, elem);
    }
    if (!set_member(opt_set, b) && !set_member(opt_set, s) && !set_member(opt_set, q)
        && !set_member(opt_set, Q)) { // print instructions if no options are selected
        printf("Select at least one sort to perform.\n");
        printf("SYNOPSIS\n");
        printf("    A collection of comparison-based sorting algorithms.\n");
        printf("\n");
        printf("USAGE\n   ./ sorting [-absqQ] [-n length] [-p elements] [-r seed]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("   -a              Enable all sorts.\n");
        printf("   -b              Enable Bubble Sort.\n");
        printf("   -s              Enable Shell Sort.\n");
        printf("   -q              Enable Quick Sort(Stack).\n");
        printf("   -Q              Enable Quick Sort(Queue).\n");
        printf("   -n length       Specify number of array elements.\n");
        printf("   -p elements     Specify number of elements to print.\n");
        printf("   -r seed         Specify random seed.\n");
        return 1;
    }
    return 0;
}
