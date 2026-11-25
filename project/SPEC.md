# ECE 361 - Project 3
## Elevator, Three Floors

### Project Overview

This project simulates an elevator that serves
three floors using the iom361 hardware model.

### Project Configuration

- Device type: C
- Key: K1
- Second structure: S5
- Report: Q5

### Elevator States

- IDLE: Waiting for a call with doors closed.
- UP: Moving up.
- DOWN: Moving down.
- DOORS_OPEN: Stopped with doors open.
- FAULT: Stopped with doors open for safety.

### Operating Rules

- The elevator starts at floor 1.
- It serves one call at a time.
- Calls received while busy are ignored.
- Moving one floor takes 6 ticks.
- Doors stay open for 8 ticks.
- Above 40.0 C, the elevator stops at the
  next floor and enters FAULT.
- The elevator leaves FAULT at or below 35.0 C.
- Every sensor reading is recorded.

### Data Structures

- Binary search tree ordered by timestamp.
- Sorted dynamic array of temperatures.
- Moving average with a window of 10 readings.
### Events and Transition Table

The elevator uses events to change between states.
Each transition has a current state, an event,
a next state, and an action.

| State | Event | Next State | Action |
|---|---|---|---|
| IDLE | EV_CALL_UP | UP | ACT_START |
| IDLE | EV_CALL_DOWN | DOWN | ACT_START |
| IDLE | EV_CALL_SAME | DOORS_OPEN | ACT_OPEN |
| IDLE | EV_OVERHEAT | FAULT | ACT_FAULT |
| IDLE | EV_FAULT_STOP | FAULT | ACT_FAULT |
| UP | EV_NEXT_FLOOR | UP | ACT_MOVE |
| UP | EV_ARRIVED | DOORS_OPEN | ACT_OPEN |
| UP | EV_OVERHEAT | UP | ACT_PENDING |
| UP | EV_FAULT_STOP | FAULT | ACT_FAULT |
| DOWN | EV_NEXT_FLOOR | DOWN | ACT_MOVE |
| DOWN | EV_ARRIVED | DOORS_OPEN | ACT_OPEN |
| DOWN | EV_OVERHEAT | DOWN | ACT_PENDING |
| DOWN | EV_FAULT_STOP | FAULT | ACT_FAULT |
| DOORS_OPEN | EV_DOOR_TIMEOUT | IDLE | ACT_CLOSE |
| DOORS_OPEN | EV_OVERHEAT | FAULT | ACT_FAULT |
| DOORS_OPEN | EV_FAULT_STOP | FAULT | ACT_FAULT |
| FAULT | EV_COOL | IDLE | ACT_RESET |

All other events, including EV_NONE, keep the
current state and use ACT_NONE.
### State Machine Diagram

```
IDLE -- Call up --> UP
IDLE -- Call down --> DOWN
IDLE -- Same floor call --> DOORS_OPEN

UP -- Arrived --> DOORS_OPEN
DOWN -- Arrived --> DOORS_OPEN

DOORS_OPEN -- Door timeout --> IDLE

IDLE -- Overheat --> FAULT
DOORS_OPEN -- Overheat --> FAULT

UP -- Overheat --> UP (fault pending)
DOWN -- Overheat --> DOWN (fault pending)

UP -- Fault stop --> FAULT
DOWN -- Fault stop --> FAULT

FAULT -- Cool --> IDLE
```

The elevator starts in IDLE. When a call is
received, it moves up or down. When it reaches
the requested floor, the doors open.

If the temperature is too high while moving,
the elevator stops at the next floor and enters
FAULT. It returns to IDLE when the temperature
is 35.0 C or lower.
### Status Word Layout

The status word is a 32-bit unsigned integer.

| Bits | Meaning |
|---|---|
| 0-2 | Current elevator state |
| 3 | Moving up |
| 4 | Moving down |
| 5 | DOORS_OPEN state |
| 6-7 | Current floor |
| 8-31 | Unused, set to zero |

### RGB Colors

| State | Color | RGB |
|---|---|---|
| IDLE | Green | 0, 255, 0 |
| UP | Blue | 0, 0, 255 |
| DOWN | Cyan | 0, 255, 255 |
| DOORS_OPEN | Yellow | 255, 255, 0 |
| FAULT | Red | 255, 0, 0 |

### Design Decisions

The elevator handles one request at a time.
New calls are ignored while the elevator is busy.
A call to the current floor opens the doors without
moving the elevator. If overheating happens while
moving, the elevator stops at the next floor for safety.

### Record Structure and Tree Storage

The record_t structure contains three fields:
- reading: The sensor reading and timestamp.
- state: The current elevator state.
- status: The 32-bit status word.

Records are stored in a binary search tree using
timestamps as keys. Smaller keys go to the left,
and larger keys go to the right.

Since timestamps usually arrive in increasing order,
a normal binary search tree could become unbalanced.
This project uses AVL rotations to keep the tree
balanced. Insertion and searching take O(log n) time.
An in-order traversal visits records in sorted order
and takes O(n) time.

### Sorted Dynamic Array

The second data structure stores temperatures in
ascending order. When a new temperature is added,
larger values are shifted to make space for it.
The array grows when more space is needed.

Binary search finds the first temperature at or above
the requested threshold. The result is the total
number of readings minus that position.
Duplicate temperatures are included in the count.

### Moving Average Report

The Q5 report calculates the moving average of the
last 10 temperature readings in timestamp order.

The first result is printed after 10 readings.
Each new reading replaces the oldest reading in
a circular buffer. A running sum is updated by
subtracting the oldest value and adding the new value.

The average is the running sum divided by 10.
Each result includes the current timestamp and
the average temperature with two decimal places.

Each update takes O(1) time. The complete report
takes O(n) time and uses O(10) extra buffer space.

### Year 2038 Problem

The Year 2038 problem happens when a signed 32-bit
Unix timestamp reaches its maximum value on
January 19, 2038, at 03:14:07 UTC.

After this time, the timestamp cannot represent
the next second correctly. This can cause problems
with storing, comparing, and displaying dates.

Using a 64-bit time_t prevents this specific problem.
The project uses time_t for timestamps, but its size
depends on the system. A 64-bit time_t should be
used for long-term operation.

### Evaluation of Elevator States

The five states make the elevator easy to understand
and test. UP and DOWN separate the two movement
directions. DOORS_OPEN controls the waiting time,
and FAULT provides a separate safety state.

One limitation is that the pending fault condition
requires extra information inside the movement
states. A separate pending fault state could make
this condition clearer, but it would also increase
the number of states and transitions.

### Comparison with an Alternative Structure

A sorted dynamic array is useful because threshold
queries take O(log n) time using binary search.
However, insertion takes O(n) time in the worst
case because existing values may need to be shifted.

An unsorted dynamic array is another option.
Adding a value takes O(1) amortized time, but
counting values at or above a threshold takes
O(n) time because every value must be checked.

Both structures use O(n) memory. The sorted array
is a good choice when fast threshold searches
are important.
