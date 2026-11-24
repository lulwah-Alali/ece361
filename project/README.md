# ECE 361 Project 3

## Elevator - Three Floors

This project simulates a three-floor elevator system.
The elevator moves between floors 1, 2, and 3.
It uses switches to receive calls and LEDs to show
its status.

## Project Features

- Elevator state machine.
- Temperature and humidity readings.
- Overheat and fault handling.
- Sensor data storage.
- Bit manipulation.
- Moving average temperature report.

## How to Build

```bash
make
```

## How to Run

```bash
./elevator scenarios/test1.txt
```

## How to Run with Report

```bash
./elevator scenarios/test1.txt --report
```

## How to Run Tests

```bash
make test
```

The bits, FSM, store, aux, and sensor tests passed.
The report test also ran without errors.

## How to Clean

```bash
make clean
```

## AI Usage

See AI_USAGE.md for details about AI assistance.
