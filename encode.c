// Darren Lee
// CSE13S
// This program implements the Huffman encoder.

#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

static uint8_t buffer[BLOCK] = { 0 }; // create buffer
uint64_t bytes_written, bytes_read;

// This function writes the tree dump to an outfile given a root node and outfile.
void postorder_tree(Node *n, int outfile) {
    uint8_t l = 'L', i = 'I';
    if (n) {
        postorder_tree(n->left, outfile);
        postorder_tree(n->right, outfile);
        if (!n->left && !n->right) { // check if the node is a leaf
            write_bytes(outfile, &l, 1);
            write_bytes(outfile, &n->symbol, 1);
        } else { // else the node is an interior node
            write_bytes(outfile, &i, 1);
        }
    }
}

int main(int argc, char **argv) {
    // unique is for counting the number of unique symbols, v is a flag for printing stats, seek is a flag for whether the file is seekable
    int opt = 0, unique = 0, v = 0, seek = 1;
    struct stat statbuf;
    // default infile is stdin, default outfile is stdout
    int infile = STDIN_FILENO, outfile = STDOUT_FILENO;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // parse the command line options
        switch (opt) {
        case 'h': // the h option specifies to print a help message then exit the program after
            fprintf(stdout, "SYNOPSIS\n");
            fprintf(stdout, "  A Huffman encoder.\n");
            fprintf(stdout, "  Compresses a file using the Huffman coding algorithm.\n");
            fprintf(stdout, "\n");
            fprintf(stdout, "USAGE\n");
            fprintf(stdout, "  ./encode [-h] [-i infile] [-o outfile]\n");
            fprintf(stdout, "\n");
            fprintf(stdout, "OPTIONS\n");
            fprintf(stdout, "  -h             Program usage and help.\n");
            fprintf(stdout, "  -v             Print compression statistics.\n");
            fprintf(stdout, "  -i infile      Input file to compress.\n");
            fprintf(stdout, "  -o outfile     Output of compressed data.\n");
            return 0;
        case 'i': infile = open(optarg, O_RDONLY); break; // i option specifies infile
        case 'o':
            // o option specifies outfile
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            break;
        case 'v': v = 1; break; // specify to print statistics
        default: // print help message and exit program if invalid option is entered
            fprintf(stdout, "SYNOPSIS\n");
            fprintf(stdout, "  A Huffman encoder.\n");
            fprintf(stdout, "  Compresses a file using the Huffman coding algorithm.\n");
            fprintf(stdout, "\n");
            fprintf(stdout, "USAGE\n");
            fprintf(stdout, "  ./encode [-h] [-i infile] [-o outfile]\n");
            fprintf(stdout, "\n");
            fprintf(stdout, "OPTIONS\n");
            fprintf(stdout, "  -h             Program usage and help.\n");
            fprintf(stdout, "  -v             Print compression statistics.\n");
            fprintf(stdout, "  -i infile      Input file to compress.\n");
            fprintf(stdout, "  -o outfile     Output of compressed data.\n");
            return 0;
        }
    }
    if (infile == -1) { // if the infile fails to open, print an error message and exit
        fprintf(stderr, "Error: Failed to open infile.\n");
        return 1;
    }
    if (outfile == -1) { // if the outfile fails to open, print an error message and exit
        fprintf(stderr, "Error: Failed to open outfile.\n");
        return 1;
    }
    if (infile == STDIN_FILENO) { // if the infile is stdin
        seek = 0; // the file is not seekable
        // create a temp file
        int tempfile = open("tempencode", O_RDWR | O_CREAT | O_TRUNC, 0600);
        int written;
        while (read_bytes(infile, buffer, 1) != 0) {
            written = write_bytes(tempfile, buffer, 1); // copy stdin to temp file
            // don't count writing to temp file when counting total bytes written
            bytes_written -= written;
        }
        infile = tempfile; // set the infile to the temp file
        lseek(infile, 0, SEEK_SET); // go to the beginning of the infile
    }
    uint64_t hist[ALPHABET] = { 0 }; // create histogram
    fstat(infile, &statbuf); // get the stats of the infile
    fchmod(outfile, statbuf.st_mode); // set the permissions of the outfile
    int c; // c counts how many bytes are returned by read_bytes
    // increment symbols 0 and 255
    hist[0]++;
    hist[255]++;
    while ((c = read_bytes(infile, buffer, BLOCK)) != 0) {
        for (int i = 0; i < c; i++) {
            // increment the counts in the histogram for each time a symbol appears
            hist[buffer[i]]++;
        }
    }
    Code table[ALPHABET] = { 0 }; // create code table
    Node *root = build_tree(hist); // build the tree
    build_codes(root, table); // build the codes and store them in the code table
    Header h;
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i]) {
            unique++; // count the number of unique symbols in the file
        }
    }
    h.magic = MAGIC; // magic number is defined by macro MAGIC in defines.h
    h.permissions = statbuf.st_mode; // set the header permissions
    h.tree_size = 3 * unique - 1; // tree size is 3*unique-1
    h.file_size = statbuf.st_size; // set the header file size
    // code for writing header inspired by Eugene's lab section on 5/18
    // write the header to outfile
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));
    postorder_tree(root, outfile); // print the tree dump
    lseek(infile, 0, SEEK_SET); // go to the beginning of the infile
    while ((c = read_bytes(infile, buffer, BLOCK)) != 0) {
        for (int i = 0; i < c; i++) { // write the code for each symbol read from the infile
            write_code(outfile, &(table[buffer[i]]));
        }
    }
    flush_codes(outfile); // flush codes left in the buffer
    if (v) { // if v flag is 1, print stats
        uint64_t uncomp_size;
        // if the file is seekable, use the header file size for uncompressed size
        if (seek) {
            uncomp_size = h.file_size;
            // else we read the file 3 times, so uncompressed size is bytes_read / 3
        } else {
            uncomp_size = bytes_read / 3;
        }
        fprintf(stderr, "Uncompressed file size: %" PRIu64 " bytes\n", uncomp_size);
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n", bytes_written);
        fprintf(stderr, "Space saving: %.2lf%%\n",
            (double) 100 * ((double) 1 - ((double) bytes_written / ((double) uncomp_size))));
    }
    delete_tree(&root);
    if (!seek) { // if the file is not seekable, remove the temp file
        unlink("tempencode");
    }
    close(infile);
    close(outfile);
    return 0;
}
