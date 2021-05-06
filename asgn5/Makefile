CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all:		encode decode error entropy

encode:		encode.o
		$(CC) -o encode.o

decode:		decode.o
		$(CC) -o decode.o

error:		error.o
		$(CC) -o error.o

entropy:	entropy.o
		$(CC) -o entropy.o

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

clean:		
		rm -f encode decode error entropy encode.o decode.o error.o entropy.o

format:		
		clang-format -i -style=file *.c *.h

scan-build: 	clean
		scan-build make
