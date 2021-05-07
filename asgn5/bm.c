#include "bm.h"

#include "bv.h"

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BYTE_SIZE 8

// struct code provided by Professor Long in assignment pdf
struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) malloc(sizeof(BitMatrix));
    m->vector = bv_create(rows * cols);
    m->rows = rows;
    m->cols = cols;
    if (!m) {
        return NULL;
    }
    for (uint32_t i = 0; i < rows * cols; i++) {
        bv_clr_bit(m->vector, i);
    }
    return m;
}

void bm_delete(BitMatrix **m) {
    free(*m);
    *m = NULL;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, r * m->rows + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * m->rows + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * m->rows + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    assert(length <= BYTE_SIZE);
    BitMatrix *m = bm_create(1, length);
    for (uint32_t i = 0; i < length; i++) {
        if (byte & (1 << i)) {
            bm_set_bit(m, 1, i);
        } else {
            bm_clr_bit(m, 1, i);
        }
    }
    return m;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t byte = 0;
    for (int i = 0; i < BYTE_SIZE; i++) {
        if (bm_get_bit(m, 1, i)) {
            byte &= (1 << i);
        }
    }
    return byte >> (m->rows * m->cols - BYTE_SIZE);
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    uint32_t c[A->rows * B->cols];
    for (uint32_t l = 0; l < A->rows * B->cols; l++) {
        c[l] = 0;
    }
    BitMatrix *m = bm_create(A->rows, B->cols);
    for (uint32_t k = 0; k < A->rows * B->cols; k++) {
        for (uint32_t i = 0; i < A->cols; i++) {
            for (uint32_t j = 0; j < B->rows; j++) {
                c[k] += bm_get_bit(A, i, j) * bm_get_bit(B, j, i);
            }
        }
        if (c[k] % 2) {
            bv_set_bit(m->vector, k);
        } else {
            bv_clr_bit(m->vector, k);
        }
    }
    return m;
}

void bm_print(BitMatrix *m) {
    bv_print(m->vector);
}

int main(void) {

    BitMatrix *G = bm_create(4, 8);
    bm_set_bit(G, 0, 0);
    bm_set_bit(G, 0, 5);
    bm_set_bit(G, 0, 6);
    bm_set_bit(G, 0, 7);
    bm_set_bit(G, 1, 1);
    bm_set_bit(G, 1, 4);
    bm_set_bit(G, 1, 6);
    bm_set_bit(G, 1, 7);
    bm_set_bit(G, 2, 2);
    bm_set_bit(G, 2, 4);
    bm_set_bit(G, 2, 5);
    bm_set_bit(G, 2, 7);
    bm_set_bit(G, 3, 3);
    bm_set_bit(G, 3, 4);
    bm_set_bit(G, 3, 5);
    bm_set_bit(G, 3, 6);
    bm_print(G);
    return 0;
}
