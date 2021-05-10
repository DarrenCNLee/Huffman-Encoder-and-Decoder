// Darren Lee
// CSE13S
// This program implements the Hamming Code module.

#include "hamming.h"

#include "stat.h"

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
    BitMatrix *m = bm_from_data(msg, NIBBLE_SIZE); // create bit matrix with lower 4 bits of msg
    BitMatrix *c = bm_multiply(m, G);
    uint8_t code = bm_to_data(c); // create code with data from c=m*G
    bm_delete(&m); // free memory allocated for bit matrices
    bm_delete(&c);
    return code;
}

// code influenced by Eugene's lab section on 5/4
HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    // create lookup table with int array
    int lookup[TABLE_SIZE] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR,
        2, HAM_ERR, 1, 0, HAM_ERR };
    BitMatrix *c = bm_from_data(code, BYTE_SIZE); // create c bit matrix from the 8 bits of code
    BitMatrix *e = bm_multiply(c, Ht);
    uint8_t err = bm_to_data(e);
    bm_delete(&e); // free memory allocated for e
    if (err == 0) { // if err is 0, no correction is needed and return HAM_OK
        *msg = lower(bm_to_data(c));
        bm_delete(&c); // free memory allocated for c
        return HAM_OK;
    }
    if (lookup[err] == HAM_ERR) {
        // if there is more than one error, do not modify message and return HAM_ERR
        uncorrected_errors++;
        bm_delete(&c);
        return HAM_ERR;
    } else { // otherwise, correct the message and return HAM_CORRECT
        if (bm_get_bit(c, 0, lookup[err])) {
            bm_clr_bit(c, 0, lookup[err]); // if the bit is 1, flip it to 0
        } else {
            bm_set_bit(c, 0, lookup[err]); // if the bit is 0, flip it to 1
        }
        *msg = lower(bm_to_data(c)); // pass the fixed message through msg
        bm_delete(&c);
        return HAM_CORRECT;
    }
}
