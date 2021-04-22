CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all:		sorting

sorting:	sorting.o bubble.o shell.o set.o
		$(CC) -o sorting sorting.o bubble.o shell.o set.o

sorting.o:	sorting.c
		$(CC) $(CFLAGS) -c sorting.c

bubble.o:	bubble.c
		$(CC) $(CFLAGS) -c bubble.c

shell.o:	shell.c
		$(CC) $(CFLAGS) -c shell.c

set.o:		set.c
		$(CC) $(CFLAGS) -c set.c

format:
		clang-format -i -style=file *.c *.h

clean:
		rm -f sorting sorting.o bubble.o shell.o 

scan-build:	clean
		scan-build make
