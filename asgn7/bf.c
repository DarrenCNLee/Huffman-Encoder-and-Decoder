// Darren Lee
// CSE13S
// This program implements the Bloom filter ADT.

#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <stdlib.h>

// struct definition provided by Professor Long in assignment pdf
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// constructor function provided by Professor Long in assignment pdf
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    if (*bf) {
        bv_delete(&(*bf)->filter); // delete the filter
        free(*bf); // free the Bloom filter
        *bf = NULL; // set the pointer to null
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    // set the bits at the indices gained from hashing the oldspeak with the 3 salts
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // check if the bits at the indices obtained by hashing the oldspeak with the salts are 1
    return (bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
            && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
            && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf)));
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bv_length(bf->filter); i++) {
        if (bv_get_bit(bf->filter, i)) { // if the bit is set
            count++; // increment count
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}
