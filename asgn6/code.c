// Darren Lee
// CSE13S
// This program implements the code ADT.

#include "code.h"

#include "defines.h"

#include <inttypes.h>
#include <stdio.h>

#define BYTE_SIZE 8

// creates a code, sets its top to 0, initializes its bits to 0
// then returns the code
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
    return !c->top; // code is empty is top is 0
}

bool code_full(Code *c) { // code is full if top equals the max code size defined by macro ALPHABET
    return c->top == ALPHABET;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false; // return false if code is full
    }
    // otherwise OR the byte top is in with bit left shifted by top mod BYTE_SIZE
    c->bits[c->top / BYTE_SIZE] |= (bit << (c->top % BYTE_SIZE));
    c->top++; // increment the top
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false; // return false if the code is empty
    }
    c->top--; // otherwise decrement the top
    // set the bit equal to the bit at top
    *bit = (c->bits[c->top / BYTE_SIZE] & (1 << (c->top % BYTE_SIZE))) >> (c->top % BYTE_SIZE);
    return true;
}

// prints each bit in the code
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%d ", (c->bits[i / BYTE_SIZE] & (1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE));
    }
    printf("\n");
}
