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
    // v is a flag for printing stats, temp is a flag for creating a temp file
    int opt = 0, v = 0, temp = 0;
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
        default: // print help message and exit program if invalid option is entered
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
            return 0;
        }
    }
    if (infile == -1) { // if infile fails to open, print error message and exit program
        fprintf(stderr, "Error: Failed to open infile.\n");
        return 1;
    }
    if (outfile == -1) { // if outfile fails to open, print error message and exit program
        fprintf(stderr, "Error: Failed to open outfile.\n");
        return 1;
    }
    if (infile == STDIN_FILENO) { // if infile is stdin
        temp = 1;
        // create a temp file
        int tempfile = open("tempdecode", O_RDWR | O_CREAT | O_TRUNC, 0600);
        int written;
        // copy stdin to temp file
        while (read_bytes(infile, buffer, 1) != 0) {
            written = write_bytes(tempfile, buffer, 1);
            // do not count bytes written to temp file for file size
            bytes_written -= written;
        }
        infile = tempfile; // set infile to temp file
        lseek(infile, 0, SEEK_SET); // go back to start of infile
    }
    Header h;
    if (read_bytes(infile, (uint8_t *) &h, sizeof(Header)) != sizeof(Header)) { // read the header
        fprintf(stderr, "Error: unable to read header.\n");
        return 1; // print error and exit if the header cannot be read
    }
    if (h.magic != MAGIC) { // print an error message if the magic number is invalid
        fprintf(stderr, "Invalid magic number.\n");
        return 1;
    }
    // set the permissions for the outfile to match the header permissions
    fchmod(outfile, h.permissions);
    uint16_t tree_size = h.tree_size;
    if (tree_size > MAX_TREE_SIZE) { // if the tree size is invalid, print an error message
        fprintf(stdout, "Error: Invalid tree size.\n");
        return 1;
    }
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
        if (temp) { // if we read the infile twice, divide by 2
            bytes_read /= 2;
        }
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n", bytes_read);
        fprintf(stderr, "Decompressed file size: %" PRIu64 " bytes\n", bytes_written);
        fprintf(stderr, "Space saving: %0.2lf%%\n",
            (double) 100 * ((double) 1 - ((double) bytes_read / (double) bytes_written)));
    }
    delete_tree(&root);
    if (temp) { // if a temp file was created
        unlink("tempdecode"); // remove it
    }
    close(infile);
    close(outfile);
    return 0;
}
