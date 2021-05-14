#include "code.h"

#include "defines.h"

#include <stdio.h>

// code provided by Professor Long in assignment pdf
typedef struct Code {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

Code code_init(void) {
    Code *c;
    c->top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        c->bits[i] = 0;
    }
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    return !c->top;
}

bool code_full(Code *c) {
    return c->top == MAX_CODE_SIZE;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if code_full (c) {
        return false;
    }
    c->bits[c->top] = bit;
    c->top++;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if code_empty (c) {
        return false;
    }
    c->top--;
    *bit = c->bit[c->top];
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf(" %" PRIu8, c->bits[i]);
    }
    printf("\n");
}
