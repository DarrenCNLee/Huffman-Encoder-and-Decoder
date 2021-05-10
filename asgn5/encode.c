// Darren Lee
// CSE13S
// This program implements the Hamming Code encoder.

#include "hamming.h"

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:"

// helper function provided by Professor Long in assignment pdf
// Returns the lower nibble of val
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// helper function provided by Professor Long in assignment pdf
// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

int main(int argc, char **argv) {
    // statbuf for file permissions; code provided by Professor Long in assigment pdf
    struct stat statbuf;
    int opt, c; // opt is for getopt, c is for fgetc
    FILE *infile = stdin, *outfile = stdout; // defaults for infile and outfile
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // if h option is selected, print out help message and exit program
            // error message inspired by program in resources repository
            fprintf(outfile, "SYNOPSIS\n");
            fprintf(outfile, "  A Hamming(8, 4) systematic code generator.\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "USAGE\n");
            fprintf(outfile, "  ./encode [-h] [-i infile] [-o outfile]\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "OPTIONS\n");
            fprintf(outfile, "  -h             Program usage and help.\n");
            fprintf(outfile, "  -i infile      Input data to encode.\n");
            fprintf(outfile, "  -o outfile     Output of encoded data.\n");
            return 0;
        case 'i': // i option specifies infile
            infile = fopen(optarg, "rb");
            break;
        case 'o': // o option specifies outfile
            outfile = fopen(optarg, "wb");
            break;
        default: // print help message and exit the program if an invalid option is entered
            fprintf(outfile, "SYNOPSIS\n");
            fprintf(outfile, "  A Hamming(8, 4) systematic code generator.\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "USAGE\n");
            fprintf(outfile, "  ./encode [-h] [-i infile] [-o outfile]\n");
            fprintf(outfile, "\n");
            fprintf(outfile, "OPTIONS\n");
            fprintf(outfile, "  -h             Program usage and help.\n");
            fprintf(outfile, "  -i infile      Input data to encode.\n");
            fprintf(outfile, "  -o outfile     Output of encoded data.\n");
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
    BitMatrix *G = bm_create(4, 8); // create generator matrix
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
    while ((c = fgetc(infile)) != EOF) { // read infile till end of file
        // encode the lower nibble and print it to the outfile
        fputc(ham_encode(G, lower_nibble(c)), outfile);
        // encode the upper nibble and print it to the outfile
        fputc(ham_encode(G, upper_nibble(c)), outfile);
    }
    fclose(infile); // close infile
    fclose(outfile); // close outfile
    bm_delete(&G); // free the memory for the generator matrix
    return 0;
}
