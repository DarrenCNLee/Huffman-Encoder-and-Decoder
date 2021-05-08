#include "hamming.h"

#include "bm.h"

#include <inttypes.h>
#include <stdio.h>
#define TABLE_SIZE  16
#define NIBBLE_SIZE 4
#define BYTE_SIZE   8

// helper function provided by Professor Long in assignment pdf
// Returns the lower nibble of val
uint8_t lower(uint8_t val) {
    return val & 0xF;
}

// code influenced by Eugene's lab section on 5/4
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *m = bm_from_data(msg, NIBBLE_SIZE);
    BitMatrix *c = bm_multiply(m, G);
    return bm_to_data(c);
}

// code influenced by Eugene's lab section on 5/4
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    int lookup[TABLE_SIZE] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR,
        2, HAM_ERR, 1, 0, HAM_ERR };
    BitMatrix *c = bm_from_data(code, BYTE_SIZE);
    BitMatrix *e = bm_multiply(c, Ht);
    uint8_t err = bm_to_data(e);
    if (err == 0) {
        *msg = lower(bm_to_data(c));
        return HAM_OK;
    }
    if (lookup[err] == HAM_ERR) {
        *msg = lower(bm_to_data(c));
        return HAM_ERR;
    } else {
        if (bm_get_bit(c, 0, lookup[err])) {
            bm_clr_bit(c, 0, lookup[err]);
        } else {
            bm_set_bit(c, 0, lookup[err]);
        }
        *msg = lower(bm_to_data(c));
        return HAM_CORRECT;
    }
}
