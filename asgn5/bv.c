#include "bv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// struct code provided by Professor Long in assignment pdf
struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    v->vector = (uint8_t *) calloc(length, sizeof(uint8_t));
    v->length = length;
    if (!v->vector) {
        free(v);
        return NULL;
    }
    for (uint32_t i = 0; i < length; i++) {
        v->vector[i] = 0;
    }
    return v;
}

void bv_delete(BitVector **v) {
    free((*v)->vector);
    free(*v);
    (*v) = NULL;
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

// code inspired by Eugene's lab section on 5/4
void bv_set_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] |= (1 << (i % 8));
}

// code inspired by Eugene's lab section on 5/4
void bv_clr_bit(BitVector *v, uint32_t i) {
    v->vector[i / 8] &= ~(1 << (i % 8));
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    return (v->vector[i / 8] & (1 << (i % 8))) >> (i % 8);
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    if (bv_get_bit(v, i) ^ bit) {
        bv_set_bit(v, i);
    } else {
        bv_clr_bit(v, i);
    }
}

void bv_print(BitVector *v) {
    for (uint32_t i = 0; i < bv_length(v); i++) {
        printf("%" PRIu8 " ", bv_get_bit(v, i));
    }
    printf("\n");
}
