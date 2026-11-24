CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

SRC = main.c sensor.c fsm.c store.c aux.c report.c bits.c iom361_r4.c
OBJ = $(SRC:.c=.o)

all: elevator

elevator: $(OBJ)
	$(CC) $(CFLAGS) -o elevator $(OBJ) -lm

test:
	$(CC) $(CFLAGS) tests/test_bits.c bits.c -o tests/test_bits
	$(CC) $(CFLAGS) tests/test_fsm.c fsm.c iom361_r4.c bits.c -lm -o tests/test_fsm
	$(CC) $(CFLAGS) tests/test_store.c store.c -o tests/test_store
	$(CC) $(CFLAGS) tests/test_aux.c aux.c -o tests/test_aux
	$(CC) $(CFLAGS) tests/test_sensor.c sensor.c -lm -o tests/test_sensor
	$(CC) $(CFLAGS) tests/test_report.c report.c store.c -lm -o tests/test_report
	./tests/test_bits
	./tests/test_fsm
	./tests/test_store
	./tests/test_aux
	./tests/test_sensor
	./tests/test_report

clean:
	rm -f $(OBJ) elevator
	rm -f tests/test_bits tests/test_fsm tests/test_store tests/test_aux tests/test_sensor tests/test_report

.PHONY: all test clean
