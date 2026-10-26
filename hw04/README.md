# ECE 361 - Homework 4

## Description
This program implements a tally abstract data type (ADT) in C. It counts how many times each name appears and stores names in alphabetical order.

## How to Build
Run:
make

## How to Test
Run:
make test

## How to Clean
Run:
make clean

## Part 3: Opaque Type

I tried to access t->n from a file that only includes tally.h.

The compiler reports an error because tally_t is an incomplete type.

This happens because the structure is defined only in tally.c, not in tally.h.

The opaque type prevents other files from accessing or changing the internal data directly. This is useful because it protects the data and allows the implementation to change without affecting other files.
