
# Homework 7 - ECE 361

## Build and Test

To build the program:
```bash
make
```

To run all tests:
```bash
make test
```

To check memory:
```bash
make memcheck
```

On macOS, to check for memory leaks:
```bash
make clean
make test
leaks --atExit -- ./tests/test_istack
```

To clean the files:
```bash
make clean
```

## Part 4 - Break It on Purpose

The three bugs will be tested one at a time. Each bug will be removed after testing.

