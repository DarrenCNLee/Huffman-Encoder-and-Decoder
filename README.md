# Huffman Coding
This program implements a Huffman coding module with an encoder and decoder.
It uses static encodings of information for data compression. For the encoder, a
code is assigned to each type of symbol in the file to compress the file. 
Shorter codes are used for symbols that are more frequent in the file, 
while longer codes are used for symbols that are less frequent. The decoder 
reads a compressed file as input and decompresses it back to its original size.

## Building
	$ make
	builds the encoder, the decoder, and the entropy-measurement program

	$ make encode
	builds just the encoder
	
	$ make decode
	builds just the decoder
	
	$ make entropy
	builds just the entropy-measurement program
## Running
	$ ./encode [-hv] [-i infile] [-o outfile]
	
	-h specifies to print usage and help message then exit program
	
	-v specifies to print out compression statistics to stderr; the statistics
	are the uncompressed file size, the compressed file size, and the space saving
	(100 * (1-(compressed size/uncompressed size)))
	
	-i infile specifies the input file to encode, the default is stdin
	
	-o outfile specifies the output file, the default is stdout

	$ ./decode [-hv] [-i infile] [-o outfile]

	-h specifies to print usage and help message then exit program
	
	-v specifies to print decompression statistics to stderr; the statistics
	are the compressed file size, the decompressed file size, and space saving
	(100*(1-(compressed size/decompressed size)))
	
	-i infile specifies the input file to decode, default is stdin
	
	-o outfile specifies the output file, default is stdout
## Cleaning
	$ make clean
## Files
	Design.pdf - The design document for the assignment; contains the purpose,
	layout, functionality, pseudocode, and draft work for the program

	Makefile - Contains the directives for building, formatting, and cleaning
	the program files.	

	encode.c - Contains the code for the Huffman encoder

	decode.c - Contains the code for the Huffman decoder
	
	entropy.c - Provided by resources repo, contains the code to measure entropy
	
	defines.h - Contains macro definitions for the assignment

	header.h - Contains struct definition for a file header.

	node.h - Contains the node ADT interface

	node.c - Contains the code for the implementation of the node ADT

	pq.h - Contains the priority queue ADT interface

	pq.c - Contains the code for the priority queue ADT

	code.h - Contains the code ADT interface

	code.c - Contains the implementation of the code ADT

	io.h - Contains the I/O module interface
	
	io.c - Contains the code for the I/O module

	stack.h - Contains the stack ADT interface

	stack.c - Contains the code for the stack ADT

	huffman.h - Contains the Huffman coding module interface

	huffman.c - Contains the code for the Huffman coding module
