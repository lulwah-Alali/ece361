CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

all: test_ht

test_ht: ht.c ht.h tests/test_ht.c
	$(CC) $(CFLAGS) -o test_ht ht.c tests/test_ht.c

test: test_ht
	./test_ht

clean:
	rm -f test_ht

.PHONY: all test clean memcheck
memcheck: test_ht
	leaks --atExit -- ./test_ht
