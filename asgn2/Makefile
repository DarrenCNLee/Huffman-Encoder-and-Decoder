CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all:		mathlib-test

mathlib-test:	mathlib-test.o mathlib.o
		$(CC) $(CFLAGS) -o mathlib-test mathlib-test.o mathlib.o $(LFLAGS)

mathlib-test.o:	mathlib-test.c 
		$(CC) $(CFLAGS) -c mathlib-test.c 

mathlib.o:	mathlib.c
		$(CC) $(CFLAGS) -c mathlib.c

clean:
		rm -f mathlib-test mathlib-test.o

scan-build:	clean
		scan-build make
