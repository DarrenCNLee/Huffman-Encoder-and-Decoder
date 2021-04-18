Darren Lee

CruzID: danalee

Spring 2021
# Assignment 2: A Small Numerical Library
This program implements a mathematical library in mathlib.c  and test harness with mathlib-test.c.

The library includes the arcSin, arcCos, arcTan, and Log functions. I used Newton's method and 
trigonometric identities to implement arcSin and trigonometric identities to implement arcCos and arcTan. 
I used Newton's method to implement the Log function. Log will only work for positive values because 0
and negative values are not in the domain of the natural log function. I used an assert macro to ensure 
that the Log function only accepts positive inputs.
## Build
	$ make
## Running
	$ ./mathlib-test -[asctl]
	
	-a option runs all tests
	-s option runs arcSin tests
	-c option runs arcCos tests
	-t option runs arcTan tests
	-l options runs Log tests
## Cleaning
	$ make clean
## Files
	mathlib.h
		Header file that has the function prototypes for the math functions in the library

	mathlib.c
		Contains math function implementations

	mathlib-test.c
		Contains main() program and serves as a test harness for math library, supports -asctl as getopt() options

	Makefile
		Contains directives to build and compile program

	DESIGN.pdf
		Contains description of program, layout and structure, functionality, pseudocode, and scratch work on paper

	WRITEUP.pdf
		Contains graphs and analysis for the differences between my library and the <math.h> library		
