CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all:		encode decode entropy

encode:		encode.o huffman.o code.o node.o pq.o io.o stack.o
		$(CC) -o encode encode.o huffman.o code.o node.o pq.o io.o stack.o

decode: 	decode.o huffman.o stack.o node.o io.o pq.o code.o
		$(CC) -o decode decode.o huffman.o stack.o node.o io.o pq.o code.o

entropy:	entropy.o
		$(CC) -o entropy entropy.o -lm

encode.o:	encode.c
		$(CC) $(CFLAGS) -c encode.c

decode.o:	decode.c
		$(CC) $(CFLAGS) -c decode.c

entropy.o:	entropy.c
		$(CC) $(CFLAGS) -c entropy.c

huffman.o:	huffman.c
		$(CC) $(CFLAGS) -c huffman.c

code.o:		code.c
		$(CC) $(CFLAGS) -c code.c

node.o:		node.c
		$(CC) $(CFLAGS) -c node.c

pq.o:		pq.c
		$(CC) $(CFLAGS) -c pq.c

io.o:		io.c
		$(CC) $(CFLAGS) -c io.c

stack.o:	stack.c
		$(CC) $(CFLAGS) -c stack.c

clean:
		rm -f encode decode entropy encode.o decode.o entropy.o huffman.o code.o node.o pq.o io.o stack.o

format:
		clang-format -i -style=file *.c *.h

scan-build:	clean
		scan-build make
