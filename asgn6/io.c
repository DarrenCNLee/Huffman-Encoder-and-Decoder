#include "io.h"

#include <inttypes.h>

static uint8_t buffer[BLOCK];
static int bufindex;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int n = 0;
    while (n < nbytes && read(infile, buf, 1) > 0) {
        n++;
    }
    return n;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int n = 0;
    while (n < nbytes && write(infile, buf, 1) > 0) {
        n++;
    }
    return n
}

// code influenced by Eugene's lab section on 5/11
bool read_bit(int infile, uint8_t *bit) {
    if (bufindex == 0) {
        read_bytes(infile, buffer, BLOCK);
    }
    *bit = buffer[bufindex];
    bufindex++;
    if (bufindex == BLOCK * 8) {
        return false;
    }
    return true;
}

// code influenced by Eugene's lab section on 5/11
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < c->top; i++) {
        if bv_get_bit (c->vector) {
            buffer[bufindex] = 1;
        } else {
            buffer[bufindex] = 0;
        }
    }
    bufindex++;
    if bufindex
        == BLOCK * 8 {
            write_bytes(outfile, buffer, BLOCK);
            bufindex = 0;
        }
}

void flush_codes(int outfile) {
    if bufindex
        > 0 {
            int offset = bufindex % BLOCK ? 1 : 0;
            write_bytes(outfile, buffer, bufindex + offset);
        }
}
