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

static uint8_t buffer[BLOCK] = { 0 };

void postorder_tree(Node *n, int outfile) {
    if (n) {
        postorder_tree(n->left, outfile);
        postorder_tree(n->right, outfile);
        if (n->left == NULL && n->right == NULL) {
            write(outfile, "L", 1);
            write_bytes(outfile, &n->symbol, 1);
        } else {
            write(outfile, "I", 1);
        }
    }
}

int main(int argc, char **argv) {
    int opt = 0, unique = 0;
    struct stat statbuf;
    int infile = 0, outfile = 1;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY); break;
        case 'v': break;
        }
    }
    uint64_t hist[ALPHABET] = { 0 };
    fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);
    int c;
    while ((c = read_bytes(infile, buffer, BLOCK)) != 0) {
        for (int i = 0; i < c; i++) {
            hist[buffer[i]]++;
        }
    }
    Code table[ALPHABET];
    Node *root = build_tree(hist);
    build_codes(root, table);
    Header h;
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i]) {
            unique++;
        }
    }
    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    h.tree_size = 3 * unique - 1;
    h.file_size = statbuf.st_size;
    write(outfile, &h, sizeof(Header));
    postorder_tree(root, outfile);
    lseek(infile, 0, SEEK_SET);
    while ((c = read_bytes(infile, buffer, BLOCK)) != 0) {
        for (int i = 0; i < c; i++) {
            write_code(outfile, &(table[buffer[i]]));
        }
    }
    flush_codes(outfile);
    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
