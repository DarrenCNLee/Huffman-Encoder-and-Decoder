#include "code.h"
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

static uint8_t buffer[BLOCK];

void postorder_tree(Node *n, FILE *outfile) {
    // uint8_t l = 'L', i = 'I';
    if (n) {
        postorder_tree(n->left, outfile);
        postorder_tree(n->right, outfile);
        if (!n->left && !n->right) {
            //   write_bytes(outfile, &l, 1);
            //  write_bytes(outfile, &n->symbol, 1);
            fprintf(outfile, "L");
            fprintf(outfile, "%" PRIu8, n->symbol);
        } else {
            //        write_bytes(outfile, &i, 1);
            fprintf(outfile, "I");
        }
    }
}

int main(int argc, char **argv) {
    int opt = 0, unique = 0;
    struct stat statbuf;
    //  int infile = 0, outfile = 1;

    FILE *infile = stdin, *outfile = stdout;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            break;
            //   case 'i': infile = open(optarg, O_RDONLY);
            //   case 'o': outfile = open(optarg, O_WRONLY);
        case 'v': break;
        }
    }
    uint64_t hist[ALPHABET];
    for (uint32_t i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }
    //    fstat(infile, &statbuf);
    //   fchmod(outfile, statbuf.st_mode);
    // for (uint32_t i = 0; i < statbuf.st_size; i++) {
    // read_bytes(infile, buffer, 1);

    //   hist[(uint8_t) buffer]++;
    // }

    int c;
    while ((c = fgetc(infile)) != EOF) {
        hist[c]++;
    }

    hist[0]++;
    hist[255]++;
    Code table[ALPHABET];
    Node *root = build_tree(hist);
    build_codes(root, table);
    Header h;
    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            unique++;
        }
    }
    h.tree_size = 3 * unique - 1;
    h.file_size = statbuf.st_size;
    // write_bytes(outfile, (uint8_t *) &h, sizeof(Header));

    write(1, &h, sizeof(Header));

    postorder_tree(root, outfile);
    //  lseek(infile, 0, SEEK_SET);
    fseek(infile, 0, SEEK_SET);
    //    for (uint32_t i = 0; i < statbuf.st_size; i++) {
    //        read_bytes(infile, buffer, 1);
    //        write_code(outfile, &table[(uint8_t) buffer]);
    //    }

    while ((c = fgetc(infile)) != EOF) {
        write_code(1, &table[(uint8_t) buffer]);
    }
    //    flush_codes(outfile);
    delete_tree(&root);
    //   close(infile);
    //  close(outfile);
    return 0;
}
