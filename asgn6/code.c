#include "code.h"

#include "defines.h"

#include <inttypes.h>
#include <stdio.h>

#define BYTE_SIZE 8

Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) {
        c.bits[i] = 0;
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
    return c->top == ALPHABET;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    c->bits[c->top / BYTE_SIZE] |= (bit << (c->top % BYTE_SIZE));
    c->top++;
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top--;
    *bit = (c->bits[c->top / BYTE_SIZE] & (1 << (c->top % BYTE_SIZE))) >> (c->top % BYTE_SIZE);
    return true;
}

void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%d ", (c->bits[i / BYTE_SIZE] & (1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE));
    }
    printf("\n");
}
