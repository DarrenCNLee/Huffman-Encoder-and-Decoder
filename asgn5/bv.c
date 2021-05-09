// Darren Lee
// CSE13S
// This program implements the bit vector ADT.

#include "bv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_SIZE 8

// struct code provided by Professor Long in assignment pdf
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// constructore function influenced by Professor Long's code on Piazza
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v) {
        uint32_t offset; // offset is 0 if the length is divisible by 8 and 1 if not divisible by 8
        if (length % BYTE_SIZE == 0) {
            offset = 0;
        } else {
            offset = 1;
        }
        v->vector = (uint8_t *) calloc(
            length / BYTE_SIZE + offset, sizeof(uint8_t)); // allocate memory for vector
        v->length = length;
        return v;
    } else { // if sufficient memory cannot be allocated, return NULL
        return NULL;
    }
}

void bv_delete(BitVector **v) {
    free((*v)->vector); // free memory allocated for vector
    free(*v); // free bit vector
    (*v) = NULL; // set pointer to NULL
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

// code inspired by Eugene's lab section on 5/4
void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / BYTE_SIZE]
        |= (1 << (i % BYTE_SIZE)); // OR the byte i is in with 1 left-shifted by i % 8
}

// code inspired by Eugene's lab section on 5/4
void bv_clr_bit(BitVector *v, uint32_t i) {
    // AND the byte i is in with the NOT of 1 left-shifted by i % 8
    v->vector[i / BYTE_SIZE] &= ~(1 << (i % BYTE_SIZE));
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    // AND the byte i is in with 1 left-shifted by 1 % 8, then shift back to the right by i % 8
    return (v->vector[i / BYTE_SIZE] & (1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE);
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    if (bv_get_bit(v, i) ^ bit) {
        bv_set_bit(v, i); // set the bit if XORing the bit gives 1
    } else {
        bv_clr_bit(v, i); // clear the bit if XORing the bit gives 0
    }
}

void bv_print(BitVector *v) {
    for (uint32_t i = 0; i < bv_length(v); i++) {
        printf("%" PRIu8 " ", bv_get_bit(v, i)); // print each bit of the bit vector
    }
    printf("\n");
}
