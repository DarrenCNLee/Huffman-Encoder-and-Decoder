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

int main(int argc, char **argv) {
    int opt = 0;
    //  struct stat statbuf;
    int infile = 0, outfile = 1;
    // FILE *infile = stdin, *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': break;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY); break;
        case 'v': break;
        }
    }
    read_bytes(infile, buffer, 4);
    // if (*buffer != MAGIC) {
    //     return 1;
    // }
    read_bytes(infile, buffer, 2);
    //    fchmod(outfile, buffer);
    read_bytes(infile, buffer, 2);
    uint16_t tree_size = *buffer;
    //  uint8_t tree_dump[tree_size];
    read_bytes(infile, buffer, 2);
    //    uint16_t file_size = buffer[0];
    for (uint16_t i = 0; i < tree_size; i++) {
        read_bytes(infile, buffer, 1);
        //       tree_dump[i] = *buffer;
    }
    //  Node *root = rebuild_tree(tree_size, tree_dump);
    //    Node *walk = root;
    //    uint8_t bit;
    //    uint32_t decoded = 0;
    //    while (decoded != file_size) {
    //       read_bit(infile, &bit);
    //        if (!walk->left && !walk->right) {
    //           write(outfile, &walk->symbol, 1);
    //            walk = root;
    //            decoded++;
    //       } else {
    //           if (!bit) {
    //                walk = walk->left;
    //           } else {
    //               walk = walk->right;
    //           }
    //      }
    //  }
    close(infile);
    close(outfile);
    return 0;
}
