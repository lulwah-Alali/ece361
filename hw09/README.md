# Homework 9 - ECE 361

## Description
This program uses a hash table to store keys and count how many times each key is added. It uses separate chaining to handle collisions.

## Build and Test
To build the program:
make

To run the tests:
make test

To check memory:
make memcheck

To clean:
make clean

## Longest Chain
In row 3, the longest chain is 10 because all the keys are multiples of 10, so many keys go into the same bucket. With 1009 buckets, these keys go into different buckets, so the longest chain is 1.

## AI Usage
I used ChatGPT to help me understand the assignment, write the code, and check my work. I ran the tests to make sure the program works.
