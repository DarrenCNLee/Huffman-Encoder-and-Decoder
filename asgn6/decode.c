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

static uint8_t buffer[BLOCK] = { 0 };

int main(int argc, char **argv) {
    int opt = 0;
    int infile = STDIN_FILENO, outfile = STDOUT_FILENO;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
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
            return 1;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY); break;
        }
    }
    Header h;
    read_bytes(infile, (uint8_t *) &h, sizeof(Header));
    if (h.magic != MAGIC) {
        fprintf(stdout, "Invalid magic number.\n");
        return 1;
    }
    fchmod(outfile, h.permissions);
    uint16_t tree_size = h.tree_size;
    uint8_t tree_dump[tree_size];
    read_bytes(infile, buffer, tree_size);
    for (uint16_t i = 0; i < tree_size; i++) {
        tree_dump[i] = buffer[i];
    }
    Node *root = rebuild_tree(tree_size, tree_dump);
    Node *walk = root;
    uint8_t bit;
    uint64_t decoded = 0;
    while (decoded != h.file_size) {
        if (walk) {
            if (!walk->left && !walk->right) {
                write_bytes(outfile, &walk->symbol, 1);
                walk = root;
                decoded++;
            }
            read_bit(infile, &bit);
            if (!bit) {
                walk = walk->left;
            } else {
                walk = walk->right;
            }
        }
    }
    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
