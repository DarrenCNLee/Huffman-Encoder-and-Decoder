
CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: sorting.o bubble.o shell.o quick.o set.o stack.o queue.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o set.o stack.o queue.o

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c 
	$(CC) $(CFLAGS) -c quick.c 

set.o:	set.c
	$(CC) $(CFLAGS) -c set.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

format:
	clang-format -i -style=file *.c *.h

clean:
	rm -f sorting sorting.o bubble.o shell.o quick.o set.o stack.o queue.o

scan-build: clean
	scan-build make

