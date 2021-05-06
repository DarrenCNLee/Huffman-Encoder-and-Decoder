#include "hamming.h"

#include "bm.h"

#define TABLE_SIZE  16
#define NIBBLE_SIZE 4

int lookup[TABLE_SIZE] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2,
    HAM_ERR, 1, 0, HAM_ERR };

// code influenced by Eugene's lab section on 5/4
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    BitMatrix *m = bm_from_data(msg, NIBBLE_SIZE);
    BitMatrix *c = bm_multiply(m, G);
    return bm_to_data(c);
}

// code influenced by Eugene's lab section on 5/4
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    BitMatrix *c = bm_from_data(code, NIBBLE_SIZE);
    BitMatrix *err = bm_multiply(c, Ht);
    uint8_t e = bm_to_data(err);
    *msg = bm_to_data(err);
    if (e == 0) {
        return HAM_OK;
    }
    if (lookup[e] == HAM_ERR) {
        return HAM_ERR;
    } else {
        return HAM_CORRECT;
    }
}
