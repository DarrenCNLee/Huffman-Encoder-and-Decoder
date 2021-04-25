#ifndef __SHELL_H__
#define __SHELL_H__

#include <stdint.h>

uint32_t s_moves, s_compares; // counts for moves and comparisons

void shell_sort(uint32_t *A, uint32_t n);

#endif
