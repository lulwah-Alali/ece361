CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

SRC = main.c sensor.c fsm.c store.c aux.c report.c bits.c iom361_r4.c
OBJ = $(SRC:.c=.o)

TESTS = tests/test_bits tests/test_fsm tests/test_store tests/test_aux tests/test_sensor tests/test_report

SCENARIOS = normal growth thresholds overheat unexpected report midnight

all: elevator

elevator: $(OBJ)
	$(CC) $(CFLAGS) -o elevator $(OBJ) -lm

test: elevator
	$(CC) $(CFLAGS) tests/test_bits.c bits.c -o tests/test_bits
	$(CC) $(CFLAGS) tests/test_fsm.c fsm.c iom361_r4.c bits.c -lm -o tests/test_fsm
	$(CC) $(CFLAGS) tests/test_store.c store.c -o tests/test_store
	$(CC) $(CFLAGS) tests/test_aux.c aux.c -o tests/test_aux
	$(CC) $(CFLAGS) tests/test_sensor.c sensor.c -lm -o tests/test_sensor
	$(CC) $(CFLAGS) tests/test_report.c report.c store.c -lm -o tests/test_report
	@passed=0; failed=0; \
	for t in $(TESTS); do \
		if ./$$t; then \
			passed=$$((passed+1)); \
		else \
			failed=$$((failed+1)); \
		fi; \
	done; \
	for s in $(SCENARIOS); do \
		mode=""; \
		if [ "$$s" = "report" ]; then mode="--report"; fi; \
		if ./elevator scenarios/$$s.txt $$mode > scenarios/$$s.actual && diff -u scenarios/$$s.expected scenarios/$$s.actual; then \
			echo "$$s: PASS"; \
			passed=$$((passed+1)); \
		else \
			echo "$$s: FAIL"; \
			failed=$$((failed+1)); \
		fi; \
	done; \
	echo "Tests passed: $$passed, Tests failed: $$failed"; \
	test $$failed -eq 0

clean:
	rm -f $(OBJ) elevator $(TESTS)
	rm -f scenarios/*.actual

.PHONY: all test clean
