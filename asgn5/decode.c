// Darren Lee
// CSE13S
// This program implements the Hamming Code decoder.

#include "hamming.h"
#include "stat.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

// helper function provided by Professor Long in assignment pdf
// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    // statbuf for file permissions; code provided by Professor Long in assigment pdf
    struct stat statbuf;
    int c_high;
    // initialize statistics
    uint32_t bytes_processed = 0, corrected_errors = 0;
    // opt is for getopt, c_low is for fgetc, stat is a flag for printing statistics
    int opt, c_low = 0, stat = 0;
    uint8_t msg_low, msg_high; // for low and high message nibbles
    FILE *infile = stdin, *outfile = stdout; // defaults for infile and outfile
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // if h option is specified, print help message and exit program after
            // error message inspired by program in resources repository
            fprintf(outfile, "SYNOPSIS\n");
            fprintf(outfile, "  A Hamming(8, 4) systematic code decoder.\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "USAGE\n");
            fprintf(outfile, "  ./decode [-h] [-v] [-i infile] [-o outfile]\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "OPTIONS\n");
            fprintf(outfile, "  -h             Program usage and help.\n");
            fprintf(outfile, "  -v             Print statistics of decoding to stderr.\n");
            fprintf(outfile, "  -i infile      Input data to decode.\n");
            fprintf(outfile, "  -o outfile     Output of decoded data.\n");
            return 0;
        case 'i': // i option specifies infile
            infile = fopen(optarg, "rb");
            break;
        case 'o': // o option specifies outfile
            outfile = fopen(optarg, "wb");
            break;
        case 'v': stat = 1; break;
        default: // if an invalid option is entered, print help message and exit program
            fprintf(outfile, "SYNOPSIS\n");
            fprintf(outfile, "  A Hamming(8, 4) systematic code decoder.\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "USAGE\n");
            fprintf(outfile, "  ./decode [-h] [-v] [-i infile] [-o outfile]\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "OPTIONS\n");
            fprintf(outfile, "  -h             Program usage and help.\n");
            fprintf(outfile, "  -v             Print statistics of decoding to stderr.\n");
            fprintf(outfile, "  -i infile      Input data to decode.\n");
            return 1;
        }
    }
    if (infile == NULL) { // print error message if opening infile failed
        fprintf(stderr, "Error: failed to open infile.\n");
        return 1;
    }
    if (outfile == NULL) { // print error message if opening outfile failed
        fprintf(stderr, "Error: failed to open outfile.\n");
        return 1;
    }
    // get the file permissions from infile; code from Professor Long in assignment pdf
    fstat(fileno(infile), &statbuf);
    // set the file permissions for outfile; code from Professor Long in assigment pdf
    fchmod(fileno(outfile), statbuf.st_mode);
    BitMatrix *Ht = bm_create(8, 4); // create H transpose matrix and set the bits
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
    while ((c_low = fgetc(infile)) != EOF) { // read infile till end of file
        // decode the lower nibble of the message
        HAM_STATUS status_low = ham_decode(Ht, c_low, &msg_low);
        bytes_processed++; // increment bytes_processed
        if (status_low == HAM_CORRECT) {
            corrected_errors++; // increment corrected_errors if an error has been corrected
        }
        // decode the upper nibble of the message
        if ((c_high = fgetc(infile)) != EOF) {
            HAM_STATUS status_high = ham_decode(Ht, c_high, &msg_high);
            if (status_high == HAM_CORRECT) {
                corrected_errors++;
            }
            bytes_processed++; // increment bytes_processed
            fputc(pack_byte(msg_high, msg_low), outfile); // print the packed byte to the outfile
        }
    }
    if (stat) { // if stat flag is 1, print the statistics for the decoder to stderr
        fprintf(stderr, "Total bytes processed: %" PRIu32 "\n", bytes_processed);
        fprintf(stderr, "Uncorrected errors: %" PRIu32 "\n", uncorrected_errors);
        fprintf(stderr, "Corrected errors: %" PRIu32 "\n", corrected_errors);
        fprintf(stderr, "Error rate: %f\n", (double) uncorrected_errors / (double) bytes_processed);
    }
    fclose(infile); // close infile
    fclose(outfile); // close outfile
    bm_delete(&Ht); // free memory allocated for H transpose matrix
    return 0;
}
