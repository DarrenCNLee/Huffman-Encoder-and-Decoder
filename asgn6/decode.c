// Darren Lee
// CSE13S
// This program implements the Huffman decoder.

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

#define OPTIONS   "hi:o:v"
#define BYTE_SIZE 8

static uint8_t buffer[BLOCK] = { 0 }; // create buffer

uint64_t bytes_written, bytes_read, decoded;

// helper function to walk the tree
void walk_tree(Node **walk, Node *root, int outfile, int infile) {
    uint8_t bit;
    if (*walk) {
        // if the current node is a leaf, write the symbol and return to the root
        if (!(*walk)->left && !(*walk)->right) {
            write_bytes(outfile, &(*walk)->symbol, 1);
            *walk = root;
            decoded++; // increment the number of symbols decoded
        }
        read_bit(infile, &bit);
        if (!bit) { // if the bit is a 0, walk down the left node
            *walk = (*walk)->left;
        } else { // if the bit is a 1, walk down the right node
            *walk = (*walk)->right;
        }
    }
}

int main(int argc, char **argv) {
    // v is a flag for printing stats
    int opt = 0, v = 0;
    int infile = STDIN_FILENO, outfile = STDOUT_FILENO; // defaults for infile and outfile
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // read options
        switch (opt) {
        case 'h': // if h option is specified, print help message and exit program after
            fprintf(stdout, "SYNOPSIS\n");
            fprintf(stdout, "  A Huffman decoder.\n");
            fprintf(stdout, "  Decompresses a file using the Huffman coding algorithm.\n");
            fprintf(stdout, "\n");
            fprintf(stdout, "USAGE\n");
            fprintf(stdout, "  ./decode [-h] [-i infile] [-o outfile]\n");
            fprintf(stdout, "\n");
            fprintf(stdout, "OPTIONS\n");
            fprintf(stdout, "  -h             Program usage and help.\n");
            fprintf(stdout, "  -v             Print compression statistics.\n");
            fprintf(stdout, "  -i infile      Input file to decompress.\n");
            fprintf(stdout, "  -o outfile     Output of decompressed data.\n");
            return 0;
        case 'i': infile = open(optarg, O_RDONLY); break; // specify infile with i option
        case 'o':
            // specify outfile with o option
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            break;
        case 'v': v = 1; break; // specify to print statistics
        }
    }
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header)); // read the header
    if (h.magic != MAGIC) { // print an error message if the magic number is invalid
        fprintf(stderr, "Invalid magic number.\n");
        return 1;
    }
    // set the permissions for the outfile to match the header permissions
    fchmod(outfile, h.permissions);
    uint16_t tree_size = h.tree_size;
    uint8_t tree_dump[tree_size]; // create a tree dump of size tree_size
    read_bytes(infile, buffer, tree_size); // read the tree dump into the buffer
    for (uint16_t i = 0; i < tree_size; i++) {
        tree_dump[i] = buffer[i]; // create the tree dump with the values read
    }
    Node *root = rebuild_tree(tree_size, tree_dump); // rebuild the tree
    Node *walk = root;
    // read until bits until the number of symbols decoded matches the file size
    while (decoded != h.file_size) {
        walk_tree(&walk, root, outfile, infile);
    }
    if (v) { // if v flag is 1, print stats
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n", bytes_read);
        fprintf(stderr, "Decompressed file size: %" PRIu64 " bytes\n", bytes_written);
        fprintf(stderr, "Space saving: %0.2lf%%\n",
            (double) 100 * ((double) 1 - ((double) bytes_read / (double) bytes_written)));
    }
    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
