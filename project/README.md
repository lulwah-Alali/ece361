# Elevator - Three Floors

This project simulates a three-floor elevator system.
The elevator moves between floors 1, 2, and 3.
It uses switches to receive calls and LEDs to show
its status.

## Project Features

- Elevator state machine.
- Temperature and humidity readings.
- Overheat and fault handling.
- AVL tree for sensor data storage.
- Sorted dynamic array with binary search.
- 32-bit status word and RGB colors.
- Moving average of 10 temperature readings.

## How to Build

```bash
make
```

## How to Run

```bash
./elevator scenarios/normal.txt
```

## How to Run with Report

```bash
./elevator scenarios/report.txt --report
```

## How to Run Tests

```bash
make test
```

The test suite runs six unit test programs and
seven scenario tests.

## Test Scenarios

- normal: Normal elevator operation.
- growth: Dynamic array growth and search.
- thresholds: Temperature and humidity thresholds.
- overheat: Overheat and fault recovery.
- unexpected: Unexpected switch inputs.
- report: Moving average report.
- midnight: Timestamp crossing midnight.

## Test Results

Tests passed: 13
Tests failed: 0

No compiler warnings were reported.

## Sanitizer Testing

```bash
make clean
make test CFLAGS="-std=c11 -Wall -Wextra -fsanitize=address,undefined -g"
```

All 13 tests passed with no reported sanitizer errors.

## How to Clean

```bash
make clean
```

## Project Documentation

See SPEC.md for design details, state transitions,
data structures, and design decisions.

## AI Usage

See AI_USAGE.md for details about AI assistance.
