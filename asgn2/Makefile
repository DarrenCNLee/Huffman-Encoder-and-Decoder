CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

all:		mathlib-test

mathlib-test:	mathlib-test.o
		$(CC) $(CFLAGS) -o mathlib-test mathlib-test.o $(LFLAGS)

mathlib-test.o:	mathlib-test.c
		$(CC) $(CFLAGS) -c mathlib-test.c 

clean:
		rm -f mathlib-test mathlib-test.o

scan-build:	clean
		scan-build make
