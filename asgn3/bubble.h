#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include <stdint.h>

int64_t b_moves, b_compares; // counts for moves and comparisons

void bubble_sort(uint32_t *A, uint32_t n);

#endif
