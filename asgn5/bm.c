// Darren Lee
// CSE13S
// This program implements the bit matrix ADT.

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
    if (m) { // initialize bit matrix if memory allocation succeeds
        m->vector = bv_create(rows * cols);
        m->rows = rows;
        m->cols = cols;
        if (!m->vector) {
            bv_delete(&m->vector);
            free(m);
            m = NULL;
        }
        return m;
    } else {
        return NULL; // return NULL if sufficient memory cannot be allocated
    }
}

void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete(&(*m)->vector); // delete the bit vector
        free(*m); // free the bit matrix
        *m = NULL; // set the bit matrix pointer to NULL
    }
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
    assert(length <= BYTE_SIZE); // maximum length is 8
    BitMatrix *m = bm_create(1, length); // create a bit matrix with 1 row and length columns
    for (uint32_t i = 0; i < length; i++) {
        if ((byte >> i) & 1) { // if the bit in byte is 1, set the bit in the bit matrix
            bm_set_bit(m, 0, i);
        }
    }
    return m;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t byte = 0;
    for (uint32_t i = 0; i < BYTE_SIZE; i++) {
        if (bm_get_bit(m, 0, i)) { // if the bit in the bit matrix is 1, set the bit in the byte
            byte |= (1 << i);
        }
    }
    return byte;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *m = bm_create(A->rows, B->cols); // create an A->rows * B->cols bit matrix
    for (uint32_t i = 0; i < A->rows; i++) {
        for (uint32_t j = 0; j < B->cols; j++) {
            uint8_t sum = 0;
            for (uint32_t k = 0; k < A->cols; k++) {
                // get dot product of A's row and B's column
                sum ^= (bm_get_bit(A, i, k) & bm_get_bit(B, k, j));
            }
            if (sum) { // if the sum is 1, set the bit in the product bit matrix
                bm_set_bit(m, i, j);
            }
        }
    }
    return m;
}

void bm_print(BitMatrix *m) {
    for (uint32_t i = 0; i < bm_rows(m); i++) {
        for (uint32_t j = 0; j < bm_cols(m); j++) {
            printf("%" PRIu8 " ", bm_get_bit(m, i, j));
            if (j == bm_cols(m) - 1) { // print each row of the bit matrix
                printf("\n");
            }
        }
    }
}
