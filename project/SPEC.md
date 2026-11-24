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
