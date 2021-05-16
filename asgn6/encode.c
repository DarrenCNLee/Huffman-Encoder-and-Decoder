#include "code.h"
#include "defines.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

int main(int argc, char **argv) {
    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': break;
        case 'i': infile = read_bytes(infile, buffer, ALPHABET); return 0;
        }
