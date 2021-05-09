CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all:		encode decode error entropy

encode:		encode.o hamming.o bm.o bv.o
		$(CC) -o encode encode.o hamming.o bm.o bv.o 

decode:		decode.o hamming.o bm.o bv.o
		$(CC) -o decode decode.o hamming.o bm.o bv.o 

error:		error.o
		$(CC) -o error error.o

entropy:	entropy.o
		$(CC) -o entropy entropy.o -lm

encode.o:	encode.c
		$(CC) $(CFLAGS) -c encode.c

decode.o:	decode.c
		$(CC) $(CFLAGS) -c decode.c

error.o: 	error.c
		$(CC) $(CFLAGS) -c error.c

entropy.o:	entropy.c
		$(CC) $(CFLAGS) -c entropy.c

hamming.o:	hamming.c 
		$(CC) $(CFLAGS) -c hamming.c 

bm.o:		bm.c
		$(CC) $(CFLAGS) -c bm.c

bv.o:		bv.c
		$(CC) $(CFLAGS) -c bv.c

clean:		
		rm -f encode decode error entropy encode.o decode.o error.o entropy.o hamming.o bm.o bv.o

format:		
		clang-format -i -style=file *.c *.h

scan-build: 	clean
		scan-build make
