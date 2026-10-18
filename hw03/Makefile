CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I.

all: ptr.o tests/test_ptr

ptr.o: ptr.c ptr.h
	$(CC) $(CFLAGS) -c ptr.c -o ptr.o

tests/test_ptr: tests/test_ptr.c ptr.o
	$(CC) $(CFLAGS) -o tests/test_ptr tests/test_ptr.c ptr.o

test: tests/test_ptr
	./tests/test_ptr

clean:
	rm -f ptr.o tests/test_ptr
