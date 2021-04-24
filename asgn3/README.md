Darren Lee

CruzID: danalee

Spring 2021
# Assignment 3: Putting your affairs in order
This program implements 4 sorting algorithms and a test harness.
The sorting algortihms are in bubble.c, shell.c, and quick.c.
The test harness is implemented in sorting.c and sorts a random array
with the different sorts.

Thee sorts are Bubble Sort, Shell Sort, and two iterative Quick Sorts. 
One of the Quick Sorts uses a stack abstract data type implmeneted in stack.c
The other Quick Sort uses a queue abstract data type implmented in queue.c.

## Build
	$ make
## Running
	$ ./sorting [-absqQ] [-n length] [-p elements] [-r seed]
	
	-a option runs all sorts
	-b option runs Bubble Sort
	-s options runs Shell Sort
	-q option runs Quick Sort that uses stack
	-Q option runs Quick Sort that uses queue
	-n length option specifies the number of elements in the array
	-p elements option specifies the number of elements to print
	-r seed option specifies the random seed for the pseudorandom numbers in the array
## Cleaning
 	$ make clean
## Files
	Design.pdf 
		Design document that explains the purpose, functionality, and layout of the program; also includes pseudocode and draft work

	Makefile
		Contains the directives for building and cleaning the sorting program

	bubble.c
		Contains C code for Bubble Sort 

	bubble.h
		Contains function prototypes for Bubble Sort

	gaps.h
		Contains Pratt gap sequence for Shell Sort

	queue.c
		Contains C code for queue abstract data type

	queue.h
		Contains function prototypes for queue

	quick.c
		Contians C code for the two Quick Sorts

	shell.c
		Contains C code for Shell Sort

	shell.h
		Contains function prototypes for Shell Sort

	sorting.c
		Contains C code for test harness for sorting algorithms

	stack.c
		Contains C code for stack abstract data type

	stack.h 
		Contains prototypes for stack	
