# AI Usage

## Tools Used

I used ChatGPT while working on this homework.

## How I Used AI

I used ChatGPT to help me:
- understand the homework requirements,
- set up the required files and folders,
- understand bit manipulation operations,
- draft and debug parts of the C code,
- create and run tests,
- understand compiler and Makefile errors,
- and document the assignment.I reviewed the code and tested it using gcc, make, and make test.

## AI Error / Correction

During the setup, AI initially treated the header files as if they already contained the required declarations. When compiling status.c, the compiler produced errors because bits.h and status.h were actually empty.

I identified the problem by inspecting the files in the terminal. I then added the required function declarations and the status_t structure to the header files and compiled the program again. After the correction, the code compiled successfully.

## Verification

I used compiler warnings and the test program to verify the implementation. The current tests complete with 32 passed and 0 failed.
