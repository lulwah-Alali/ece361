# ECE 361 Homework 1

This homework implements a small C library for bit manipulation and for unpacking a 16-bit thermostat status word.

## Build and Test

Run:

make

Then run the tests with:

make test

Clean the generated build files with:

make clean

## Valid Input Ranges

For get_field and set_field:
- width must be from 1 to 32.
- pos must be from 0 to 31.
- pos + width must be at most 32.

For sign_extend:
- width must be from 1 to 32.

For out-of-range arguments, get_field returns 0 and set_field returns the original word.

## Boundary Behavior

The functions support width values from 1 through 32. A width of 32 is handled separately to avoid shifting by 32 bits.

set_field uses only the lowest width bits of value when replacing a field.

sign_extend interprets the lowest width bits as a two's complement signed value.

## Thermostat Status

status_unpack extracts the HEAT, COOL, FAN, FAULT, MODE, reserved, and SETPOINT fields from the 16-bit status word.

Modes 0 through 4 are valid. Modes 5 through 7 are invalid. For an invalid mode, status_unpack reports the mode value as it appears in the status word.
