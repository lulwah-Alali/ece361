
CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
SANFLAGS = -fsanitize=address,undefined

.PHONY: all test memcheck clean

all: balance

balance: balance.c istack.c istack.h
	$(CC) $(CFLAGS) balance.c istack.c -o balance

tests/test_istack: tests/test_istack.c istack.c istack.h
	$(CC) $(CFLAGS) tests/test_istack.c istack.c -o tests/test_istack

test: balance tests/test_istack
	./tests/test_istack
	./regress.sh

memcheck:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" test

clean:
	rm -f balance tests/test_istack *.o

