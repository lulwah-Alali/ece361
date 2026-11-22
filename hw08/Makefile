
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
TARGET = treestats
TEST = test_bst

.PHONY: all test memcheck clean

all: $(TARGET)

$(TARGET): bst.c bst.h treestats.c
	$(CC) $(CFLAGS) bst.c treestats.c -o $(TARGET)

$(TEST): bst.c bst.h tests/test_bst.c
	$(CC) $(CFLAGS) bst.c tests/test_bst.c -o $(TEST)

test: $(TEST)
	./$(TEST)

memcheck: $(TEST)
	leaks --atExit -- ./$(TEST)

clean:
	rm -f $(TARGET) $(TEST) *.o

