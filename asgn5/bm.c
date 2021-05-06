#include "bm.h"

#include "bv.h"

#include <assert.h>
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
    if (!m) {
        return NULL;
    }
    for (uint32_t i = 0; i < rows * cols; i++) {
        m->vector[i] = 0;
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
    BitMatrix *b = bm_create(1, BYTE_SIZE);
    BitMatrix *m = bm_create(1, length);
    for (uint32_t i = 0; i < length; i++) {
        if (bm_get_bit(b, 1, i)) {
            bm_set_bit(m, 1, i);
        }
    }
    return m;
}

uint8_t bm_to_data(BitMatrix *m) {
    return m >> (m->rows * m->cols - BYTE_SIZE);
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *m = bm_create(A->rows, B->cols);
    for (uint32_t k = 0; k < A->rows * b->cols; k++) {
        for (uint32_t i = 0; i < A->cols; i++) {
            for (uint32_t j = 0; j < B->rows; j++) {
                m->vector[k] += bm_get_bit(A, i, j) * bm_get_bit(B, j, i);
            }
        }
        m->vector[k] %= 2;
    }
    return m;
}

void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
            printf("%" PRIu32, m->vector(i * m->rows + j));
        }
        printf("\n");
    }
}
