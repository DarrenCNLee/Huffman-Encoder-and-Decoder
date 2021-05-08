#include "hamming.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "hi:o:v"

// helper function provided by Professor Long in assignment pdf
// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    int opt, c_low = 0;
    uint8_t msg_low, msg_high;
    FILE *infile = stdin, *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': break;
        case 'i': fopen(optarg, "r"); break;
        case 'o': fopen(optarg, "w"); break;
        case 'v': break;
        }
    }
    BitMatrix *Ht = bm_create(8, 4);
    bm_set_bit(Ht, 0, 1);
    bm_set_bit(Ht, 0, 2);
    bm_set_bit(Ht, 0, 3);
    bm_set_bit(Ht, 1, 0);
    bm_set_bit(Ht, 1, 2);
    bm_set_bit(Ht, 1, 3);
    bm_set_bit(Ht, 2, 0);
    bm_set_bit(Ht, 2, 1);
    bm_set_bit(Ht, 2, 3);
    bm_set_bit(Ht, 3, 0);
    bm_set_bit(Ht, 3, 1);
    bm_set_bit(Ht, 3, 2);
    bm_set_bit(Ht, 4, 0);
    bm_set_bit(Ht, 5, 1);
    bm_set_bit(Ht, 6, 2);
    bm_set_bit(Ht, 7, 3);
    while ((c_low = fgetc(infile)) != EOF) {
        ham_decode(Ht, c_low, &msg_low);
        ham_decode(Ht, fgetc(infile), &msg_high);
        fputc(pack_byte(msg_high, msg_low), outfile);
    }
    fclose(infile);
    fclose(outfile);
    bm_delete(&Ht);
    return 0;
}
