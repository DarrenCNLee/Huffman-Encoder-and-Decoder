Darren Lee

CruzID: danalee

Spring 2021
# Assignment 5: Hamming Codes
This program implements an encoder and decoder that use the Hamming (8,4)
systematic code to encode and decode messages. This allows one error to be
corrected and multiple errors to be detected. If the program can correct the
error, it does so and decodes the message. If there is no error, the message
does not need correction. Otherwise, there is an uncorrectable error and the 
program does not modify the message.

## Building
	$ make
## Running
	$ ./encode [-h] [-i infile] [-o outfile]
	
	-h specifies to print usage and help message then exit program
	-i infile specifies the file for input, default is stdin
	-o outfile specifies the file for output, default is stdout

	$ ./decode [-h] [-v] [-i infile] [-o outfile]
	
	-h specifies to print usage and help message then exit program	
	-v specifies to print out statistics of decoding to stderr
	-i infile specifies the file for input, default is stdin
	-o outfile specifies the file for output, default is stdout
## Cleaning 
	$ make clean
## Files
	DESIGN.pdf - This design document has the purpose, layout, functionality,
	and draft work for the program.

	Makefile - Contains the directives for building, formatting, and cleaning
	the program files

	bm.c - Contains the code for the implementation of the bit matrix ADT

	bm.h - Contains the interface for the bit matrix ADT
	
	bv.c - Contains the code for the implementation of the bit vector ADT
	
	bv.h - Contains the interface for the bit vector ADT

	decode.c - Contains the code for the decoder

	encode.c - Contains the code for the encoder

	error.c - Contains the code to inject errors into codes 

	entropy.c - Contains the code to measure entropy

	hamming.c - Contains the code for the implementation of the Hamming Code module

	hamming.h - Contains the interface for the Hamming Code module

	stat.h - Contains the declaration for the uncorrected_errors variable to count how many errors are left uncorrected when decoding

	WRITEUP.pdf - Contains graphs showing the amount of entropy before and after encoding and analysis of the graphs
