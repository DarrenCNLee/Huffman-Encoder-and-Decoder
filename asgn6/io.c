#include "io.h"

#include <inttypes.h>
#include <unistd.h>

#define BYTE_SIZE 8

static uint8_t buffer[BLOCK];
static int bufindex;

// code influenced by Sahiti's lab section on 5/12
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0, bytes = 0;
    while (bytes > 0 && total != nbytes) {
        bytes = read(infile, buf, nbytes - total);
        total += bytes;
    }
    return total;
}

// code influenced by Sahiti's lab section on 5/12
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0, bytes = 0;
    while (bytes > 0 && total != nbytes) {
        bytes = write(outfile, buf, nbytes - total);
        total += bytes;
    }
    return total;
}

// code influenced by Eugene's lab section on 5/11
bool read_bit(int infile, uint8_t *bit) {
    if (bufindex == 0) {
        read_bytes(infile, buffer, BLOCK);
    }
    *bit = (buffer[bufindex / BYTE_SIZE] & (1 << (bufindex % BYTE_SIZE))) >> (bufindex % BYTE_SIZE);
    bufindex++;
    if (bufindex == BLOCK * 8) {
        return false;
    }
    return true;
}

// code influenced by Eugene's lab section on 5/11
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        if ((c->bits[i / BYTE_SIZE] & (1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE)) {
            buffer[i / BYTE_SIZE] |= (1 << (i % BYTE_SIZE));
        } else {
            buffer[i / BYTE_SIZE] &= ~(1 << (i % BYTE_SIZE));
        }
    }
    bufindex++;
    if (bufindex == BLOCK * 8) {
        write_bytes(outfile, buffer, BLOCK);
        bufindex = 0;
    }
}

void flush_codes(int outfile) {
    if (bufindex > 0) {
        int offset = bufindex % BLOCK ? 1 : 0;
        write_bytes(outfile, buffer, bufindex + offset);
    }
}
