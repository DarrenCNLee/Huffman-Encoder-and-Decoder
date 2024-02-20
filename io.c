// Darren Lee
// CSE13S
// This program implements the I/O module.

#include "io.h"

#include <inttypes.h>
#include <unistd.h>

#define BYTE_SIZE 8

static uint8_t buffer[BLOCK] = { 0 }; // create buffer
static uint32_t bufindex; // create buffer index

// helper function to get the bit of a code at index i
uint8_t code_get_bit(Code *c, uint32_t i) {
    // AND the byte i is in with 1 left-shifted by 1 % 8, then shift back to the right by i % 8
    return (c->bits[i / BYTE_SIZE] & ((uint64_t) 1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE);
}

// helper function to get the bit of a buffer at index i
uint8_t buf_get_bit(uint8_t *buf, uint32_t i) {
    // AND the byte i is in with 1 left-shifted by 1 % 8, then shift back to the right by i % 8
    return (buf[i / BYTE_SIZE] & ((uint64_t) 1 << (i % BYTE_SIZE))) >> (i % BYTE_SIZE);
}

// helper function to set the bit of a buffer at index i to 1
void buf_set_bit(uint8_t *buf, uint32_t i) {
    buf[i / BYTE_SIZE] |= ((uint64_t) 1 << (i % BYTE_SIZE));
}

// helper function to clear the bit of a buffer at index i to 0
void buf_clr_bit(uint8_t *buf, uint32_t i) {
    buf[i / BYTE_SIZE] &= ~((uint64_t) 1 << (i % BYTE_SIZE));
}

// code influenced by Sahiti's lab section on 5/12
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int total = 0, bytes = 0; // initialize total and bytes

    while (true) {
        if ((bytes = read(infile, buf + total, nbytes)) <= 0) {
            break;
        }

        total += bytes;
        if (total == nbytes) {
            break;
        }
    }
    
    bytes_read += total;
    return total;
        
    while (total != nbytes) { // read until total is at least nbytes
        // read nbytes-total and store number of bytes read in bytes
        bytes = read(infile, buf, nbytes - total);
        if (!bytes) { // if bytes is 0, break the while loop
            break;
        }
        total += bytes; // total increases by bytes
    }
    bytes_read += total;
    return total; // return total number of bytes read
}

// code influenced by Sahiti's lab section on 5/12
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int total = 0, bytes = 0; // initialize total and bytes

    while (true) {
        if ((bytes = write(outfile, buf + total, nbytes)) <= 0) {
            break;
        }

        total += bytes;

        if (total == nbytes) {
            break;
        }
    }
    
    bytes_written += total;
    return total;
    
    while (total != nbytes) { // write until total is at least nbytes
        // write nbytes-total and store the number of bytes written in bytes
        bytes = write(outfile, buf, nbytes - total);
        if (!bytes) { // if bytes is 0, break the while loop
            break;
        }
        total += bytes; // increase total by bytes
    }
    bytes_written += total;
    return total; // return the total number of bytes written
}

// code influenced by Eugene's lab section on 5/11
bool read_bit(int infile, uint8_t *bit) {
    uint32_t last_bit = 0, read = 0; // last_bit will be the last_bit in the file
    if (!bufindex) { // if bufindex is 0 and the buffer is empty, read a block
        read = read_bytes(infile, buffer, BLOCK);
        if (read < BLOCK) {
            // if the number of bytes read is less than a block, last_bit is read*8+1
            last_bit = read * BYTE_SIZE + 1;
        }
    }
    *bit = buf_get_bit(buffer, bufindex); // store the bit at the buffer index in the buffer in bit
    bufindex++; // increment the buffer index
    if (bufindex == BLOCK * BYTE_SIZE) { // if the buffer is full
        bufindex = 0; // reset the buffer index
    }

    return bufindex != last_bit; 
        
    if (bufindex == last_bit) { // if the buffer index is the last bit, return false
        return false;
    } else { // else return true
        return true;
    }
}

// code influenced by Eugene's lab section on 5/11
void write_code(int outfile, Code *c) {
    for (uint32_t i = 0; i < code_size(c); i++) {
        if (code_get_bit(c, i)) { // if the bit in the code at i is 1
            buf_set_bit(buffer, bufindex); // set the bit in the buffer at the buffer index
        } else { // else the bit in the code is 0
            buf_clr_bit(buffer, bufindex); // clear the bit in the buffer at the buffer index
        }
        bufindex++; // increment the buffer index
        if (bufindex == BLOCK * BYTE_SIZE) { // if the buffer is full
            write_bytes(outfile, buffer, BLOCK); // write a BLOCK to the outfile
            bufindex = 0; // reset the buffer index
        }
    }
}

void flush_codes(int outfile) {
    if (bufindex > 0) { // if the buffer index is greater than 0 and the buffer is not empty
        // write buffer index/8 bytes + an extra byte if there is a remainder when dividing by 8
        write_bytes(outfile, buffer, bufindex / BYTE_SIZE + (bufindex % BYTE_SIZE ? 1 : 0));
    }
}
