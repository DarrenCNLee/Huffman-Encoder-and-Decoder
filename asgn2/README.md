Darren Lee

CruzID: danalee

Spring 2021
# Assignment 2: A Small Numerical Library
This program implements a mathematical library and test harness.

The library includes the arcSin, arcCos, arcTan, and Log functions. I used the inverse method
to implement arcSin and trigonometric identities to implement arcCos and arcTan. I used Newton's
method to implement the Log function.
## Build
	$ make
## Running
	$ ./mathlib-test -[asctl]
## Cleaning
	$ make clean
## Files
	mathlib.h
		Header file that has the function prototypes for the math functions in the library

	mathlib.c
		Contains math function implementations

	mathlib-test.c
		Contains main() porgram and serves as a test harness for math library, supports -asctl as getopt() options

	Makefile
		Contains directives to build and compile program

	DESIGN.pdf
		Contains description of program, layout and structure, functionality, pseudocode, and scratch work on paper

	WRITEUP.pdf
		Contains analysis for the differences between my library and the <math.h> library		
