#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "sensor.h"

typedef enum {
    IDLE,
    UP,
    DOWN,
    DOORS_OPEN,
    FAULT,
    STATE_COUNT
} state_t;

typedef enum {
    EV_NONE,
    EV_CALL_UP,
    EV_CALL_DOWN,
    EV_CALL_SAME,
    EV_NEXT_FLOOR,
    EV_ARRIVED,
    EV_DOOR_TIMEOUT,
    EV_OVERHEAT,
    EV_FAULT_STOP,
    EV_COOL,
    EVENT_COUNT
} event_t;

typedef struct {
    state_t state;
    int current_floor;
    int target_floor;
    time_t state_since;
    time_t move_since;
    uint32_t previous_switches;
    bool fault_pending;
} elevator_t;

void fsm_init(elevator_t *elevator, time_t now);

state_t fsm_transition(elevator_t *elevator,
                       event_t event, time_t now);

void fsm_step(elevator_t *elevator,
              const reading_t *reading,
              uint32_t switches);

uint32_t fsm_leds(state_t state);
uint32_t fsm_rgb(state_t state);

#endif
