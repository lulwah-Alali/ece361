# ECE 361 – Homework 2

## Description
This program reads sensor data containing a tick, temperature, and humidity. It calculates minimum, maximum, and average values, finds the longest consecutive run above a temperature threshold, and displays a temperature histogram.

The program is organized into separate C modules:
- `main.c` – Main program and output
- `reading.c` / `reading.h` – Reading and parsing sensor data
- `stats.c` / `stats.h` – Statistical calculations
- `histogram.c` / `histogram.h` – Temperature histogram

## Compilation
gcc -std=c11 -Wall -Wextra -o readings main.c reading.c stats.c histogram.c

## Running
./readings < data/normal.txt

To specify a temperature threshold:

./readings 25 < data/edge.txt

The default threshold is 30.0°C.

## Testing
Run the regression tests:

bash regress.sh

All four provided regression tests passed.