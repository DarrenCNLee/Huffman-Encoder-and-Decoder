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
    bv_delete(&(*m)->vector);
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
    bv_set_bit(m->vector, r * bm_cols(m) + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, r * bm_cols(m) + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, r * bm_cols(m) + c);
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
    uint8_t c[A->rows * B->cols];
    for (uint32_t l = 0; l < A->rows * B->cols; l++) {
        c[l] = 0;
    }
    BitMatrix *m = bm_create(A->rows, B->cols);
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < B->cols; j++) {
            for (uint32_t k = 0; k < A->cols; k++) {
                c[i * B->cols + j] += (bm_get_bit(A, i, k) * bm_get_bit(B, k, j));
            }
        }
    }
    for (uint32_t l = 0; l < A->rows * B->cols; l++) {
        if (c[l] % 2) {
            bv_set_bit(m->vector, l);
        } else {
            bv_clr_bit(m->vector, l);
        }
    }
    return m;
}

void bm_print(BitMatrix *m) {
    for (uint32_t j = 0; j < bm_rows(m); j++) {
        for (uint32_t i = 0; i < bm_cols(m); i++) {
            printf("%" PRIu8 " ", bm_get_bit(m, j, i));
            if (i == bm_cols(m) - 1) {
                printf("\n");
            }
        }
    }
}
