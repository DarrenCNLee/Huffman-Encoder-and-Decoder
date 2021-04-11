CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all:		mathlib-test

mathlib-test:	mathlib-test.o
		$(CC) -o mathlib-test mathlib-test.o mathlib.o -lm

mathlib-test.o:	mathlib-test.c
		$(CC) $(CFLAGS) -c mathlib-test 

clean:
		rm -f mathlib-test mathlib-test.o

scan-build:	clean
		scan-build make
