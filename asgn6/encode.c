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

void postorder_tree(Node *n, int outfile) {
    //   uint8_t l = 'L', i = 'I';
    if (n) {
        postorder_tree(n->left, outfile);
        postorder_tree(n->right, outfile);
        if (n->left == NULL && n->right == NULL) {
            write(outfile, "L", 1);
            write(outfile, &((char) n->symbol), 1);
            //        printf("L");
            //       printf("%c", n->symbol);
        } else {
            write(outfile, "I", 1);
            // printf("I");
        }
    }
}

int main(int argc, char **argv) {
    int opt = 0, unique = 0;
    struct stat statbuf;
    int infile = 0, outfile = 1;

    // FILE *infile = stdin, *outfile = stdout;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': break;
        case 'i': infile = open(optarg, O_RDONLY);
        case 'o': outfile = open(optarg, O_WRONLY);
        case 'v': break;
        }
    }
    uint64_t hist[ALPHABET];
    for (uint32_t i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }
    fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);
    //  fstat(fileno(infile), &statbuf);
    //  fchmod(fileno(outfile), statbuf.st_mode);
    for (uint32_t i = 0; i < statbuf.st_size; i++) {
        read_bytes(infile, buffer, 1);
        hist[(uint8_t) buffer]++;
    }
    //  int c;
    //  while ((c = fgetc(infile)) != EOF) {
    //      hist[c]++;
    //  }

    Code table[ALPHABET];
    for (uint32_t i = 0; i < ALPHABET; i++) {
        table[i] = code_init();
    }
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
    write(outfile, &h, sizeof(Header));
    postorder_tree(root, outfile);
    lseek(infile, 0, SEEK_SET);
    // fseek(infile, 0, SEEK_SET);
    for (uint32_t i = 0; i < statbuf.st_size; i++) {
        read_bytes(infile, buffer, 1);
        write_code(outfile, &table[(uint8_t) buffer]);
    }

    //  while ((c = fgetc(infile)) != EOF) {
    //      write_code(1, &table[c]);
    //  }
    flush_codes(outfile);
    delete_tree(&root);
    close(infile);
    close(outfile);
    return 0;
}
