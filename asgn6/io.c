#include "io.h"

#include <inttypes.h>
#include <unistd.h>

#define BYTE_SIZE 8

static uint8_t buffer[BLOCK] = { 0 };
static uint32_t bufindex;

uint8_t code_get_bit(Code *c, uint32_t i) {
    // AND the byte i is in with 1 left-shifted by 1 % 8, then shift back to the right by i % 8
    return (c->bits[i / BYTE_SIZE] & (1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE);
}

uint8_t buf_get_bit(uint8_t *buf, uint32_t i) {
    // AND the byte i is in with 1 left-shifted by 1 % 8, then shift back to the right by i % 8
    return (buf[i / BYTE_SIZE] & (1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE);
}

void buf_set_bit(uint8_t *buf, uint32_t i) {
    buf[i / BYTE_SIZE] |= ((uint64_t) 1 << (i % BYTE_SIZE));
}

void buf_clr_bit(uint8_t *buf, uint32_t i) {
    buf[i / BYTE_SIZE] &= ~((uint64_t) 1 << (i % BYTE_SIZE));
}

// code influenced by Sahiti's lab section on 5/12
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0, bytes = 0;
    while (total < nbytes) {
        bytes = read(infile, buf, nbytes - total);
        if (!bytes) {
            break;
        }
        total += bytes;
    }
    return total;
}

// code influenced by Sahiti's lab section on 5/12
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0, bytes = 0;
    while (total < nbytes) {
        bytes = write(outfile, buf, nbytes - total);
        if (!bytes) {
            break;
        }
        total += bytes;
    }
    return total;
}

// code influenced by Eugene's lab section on 5/11
bool read_bit(int infile, uint8_t *bit) {
    int bytes_read = 0;
    uint32_t last_bit = 0;
    if (!bufindex) {
        bytes_read = read_bytes(infile, buffer, BLOCK);
        if (bytes_read < BLOCK) {
            last_bit = bytes_read * BYTE_SIZE + 1;
        }
    }
    *bit = buf_get_bit(buffer, bufindex);
    bufindex++;
    if (bufindex == BLOCK * BYTE_SIZE) {
        bufindex = 0;
    }
    if (bufindex == last_bit) {
        return false;
    } else {
        return true;
    }
}

// code influenced by Eugene's lab section on 5/11
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        if (code_get_bit(c, i)) {
            buf_set_bit(buffer, bufindex);
        } else {
            buf_clr_bit(buffer, bufindex);
        }
        bufindex++;
        if (bufindex == BLOCK * BYTE_SIZE) {
            write_bytes(outfile, buffer, BLOCK);
            bufindex = 0;
        }
    }
}

void flush_codes(int outfile) {
    if (bufindex > 0) {
        write_bytes(outfile, buffer, bufindex / BYTE_SIZE + (bufindex % BYTE_SIZE ? 1 : 0));
    }
}
