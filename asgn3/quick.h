#ifndef __QUICK_H__
#define __QUICK_H__

#include <stdint.h>

int64_t q_moves, q_compares; // counts for moves and comparisons
extern uint32_t max_stack_size;
extern uint32_t max_queue_size;

void quick_sort_stack(uint32_t *A, uint32_t n);

void quick_sort_queue(uint32_t *A, uint32_t n);

#endif
