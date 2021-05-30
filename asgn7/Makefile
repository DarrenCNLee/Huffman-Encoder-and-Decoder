CC=clang
CFLAGS= -Wall -Wextra -Werror -Wpedantic

all:		banhammer

banhammer:	banhammer.o
		$(CC) -o banhammer banhammer.o

banhammer.o:	banhammer.c
		$(CC) $(CFLAGS) -c banhammer.c

speck.o:	speck.c
		$(CC) $(CFLAGS) -c speck.c

ht.o:		ht.c
		$(CC) $(CFLAGS) -c ht.c

ll.o:		ll.c
		$(CC) $(CFLAGS) -c ll.c

node.o:		node.c
		$(CC) $(CFLAGS) -c node.c

bf.o:		bf.c
		$(CC) $(CFLAGS) -c bf.c

bv.o:		bv.c
		$(CC) $(CFLAGS) -c bv.c

parser.o:	parser.c
		$(CC) $(CFLAGS) -c parser.c

format:		
		clang-format -i -style=file *.c *.h

clean:		
		rm -f banhammer banhammer.o speck.o ht.o ll.o node.o bf.o bv.o parser.o

scan-build:	clean
		scan-build make
