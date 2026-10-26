CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

all: events

events: events.o tally.o
	$(CC) $(CFLAGS) -o events events.o tally.o

events.o: events.c tally.h
	$(CC) $(CFLAGS) -c events.c

tally.o: tally.c tally.h
	$(CC) $(CFLAGS) -c tally.c

tests/test_tally: tests/test_tally.c tally.o tally.h
	$(CC) $(CFLAGS) -o tests/test_tally tests/test_tally.c tally.o

test: tests/test_tally
	./tests/test_tally

clean:
	rm -f events *.o tests/test_tally

.PHONY: all test cleanø

