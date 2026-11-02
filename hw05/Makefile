
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: lock

lock: main.o lock.o
	$(CC) $(CFLAGS) -o lock main.o lock.o

main.o: main.c lock.h
	$(CC) $(CFLAGS) -c main.c

lock.o: lock.c lock.h
	$(CC) $(CFLAGS) -c lock.c

test_lock: tests/test_lock.c lock.c lock.h
	$(CC) $(CFLAGS) -o test_lock tests/test_lock.c lock.c

test: test_lock
	./test_lock

clean:
	rm -f lock test_lock *.o

.PHONY: all test clean

