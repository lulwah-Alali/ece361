CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

all: bits.o status.o

bits.o: bits.c bits.h
	$(CC) $(CFLAGS) -c bits.c

status.o: status.c status.h bits.h
	$(CC) $(CFLAGS) -c status.c

tests/test_bits: tests/test_bits.c bits.o status.o
	$(CC) $(CFLAGS) -I. tests/test_bits.c bits.o status.o -o tests/test_bits

test: tests/test_bits
	./tests/test_bits

clean:
	rm -f bits.o status.o tests/test_bits test_bits
