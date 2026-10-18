CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

all: readings

readings: main.c reading.c stats.c histogram.c
	$(CC) $(CFLAGS) -o readings main.c reading.c stats.c histogram.c

tests/test_stats: tests/test_stats.c stats.c stats.h
	$(CC) $(CFLAGS) -o tests/test_stats tests/test_stats.c stats.c -lm

test: readings tests/test_stats
	bash regress.sh
	./tests/test_stats

clean:
	rm -f readings tests/test_stats
