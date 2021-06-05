Darren Lee

CruzID: danalee

Spring 2021
# Assignment 7: The Great Firewall of Santa Cruz Bloom Filters, Linked Lists and Hash Tables
This program implements a Bloom filter that checks for badspeak and oldspeak words
and issues warnings based on what crimes the citizen using these words has committed.
The Bloom filter uses a SPECK block cipher as a has function to create a hash table.
The hash table stores translations from oldspeak to newspeak as well as oldspeak words
without translations, known as badspeak words. Linked lists are used in the hash table
to resolve hash collisions.

## Building
	$ make
## Running
	$ ./banhammer [-hsm] [-t size] [-f size]
	
	-h specifies to print program usage and help message
	-s specifies to print program statistics
	-m specified to enable move-to-front rule
	-t size specifies hash table size (default is 10000)
	-f size specifies Bloom filter size (default is 2^20)
## Cleaning
	$ make clean
## Files
	banhammer.c - contains the main program 
	messages.h - contains definitions for mixspeak, badspeak, and goodspeak messages
	speck.h - contains interface for the SPECK cipher hash function
	speck.c - provided by course repo, contains the implementation of the SPECK cipher hash function
	ht.h - contains the interface for the hash table ADT
	ht.c - contains the implementation for the hash table ADT
	ll.h - contains the interface for the linked list ADT
	ll.c - contains the implementation for the linked list ADT
	node.h - contains the interface for the node ADT
	node.c - contains the implmentation for the ndoe ADT
	bf.h - contains the interface for the Bloom filter ADT
	bf.c - contains the implementation for the Bloom filter ADT
	bv.h - contains the interface for the bit vector ADT
	bv.c - contains the implementation for the bit vector ADT
	parser.h - contains the interface for the regex parsing module
	parser.c - contains the implementation of the regex parsing module
	Makefile - contains directives for building, formatting, and cleaning files
	DESIGN.pdf - contains purpose, layout, and functionality of the program as well
	as supporting pseudocode
