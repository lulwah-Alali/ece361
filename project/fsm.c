#include "fsm.h"
#include "iom361_r4.h"

typedef enum {
    ACT_NONE,
    ACT_START,
    ACT_MOVE,
    ACT_OPEN,
    ACT_CLOSE,
    ACT_PENDING,
    ACT_FAULT,
    ACT_RESET
} action_t;

typedef struct {
    state_t next;
    action_t action;
} transition_t;

static const transition_t table[STATE_COUNT][EVENT_COUNT] = {
    [IDLE] = {
        {IDLE, ACT_NONE},
        {UP, ACT_START},
        {DOWN, ACT_START},
        {DOORS_OPEN, ACT_OPEN},
        {IDLE, ACT_NONE},
        {IDLE, ACT_NONE},
        {IDLE, ACT_NONE},
        {FAULT, ACT_FAULT},
        {FAULT, ACT_FAULT},
        {IDLE, ACT_NONE}
    },
    [UP] = {
        {UP, ACT_NONE},
        {UP, ACT_NONE},
        {UP, ACT_NONE},
        {UP, ACT_NONE},
        {UP, ACT_MOVE},
        {DOORS_OPEN, ACT_OPEN},
        {UP, ACT_NONE},
        {UP, ACT_PENDING},
        {FAULT, ACT_FAULT},
        {UP, ACT_NONE}
    },
    [DOWN] = {
        {DOWN, ACT_NONE},
        {DOWN, ACT_NONE},
        {DOWN, ACT_NONE},
        {DOWN, ACT_NONE},
        {DOWN, ACT_MOVE},
        {DOORS_OPEN, ACT_OPEN},
        {DOWN, ACT_NONE},
        {DOWN, ACT_PENDING},
        {FAULT, ACT_FAULT},
        {DOWN, ACT_NONE}
    },
    [DOORS_OPEN] = {
        {DOORS_OPEN, ACT_NONE},
        {DOORS_OPEN, ACT_NONE},
        {DOORS_OPEN, ACT_NONE},
        {DOORS_OPEN, ACT_NONE},
        {DOORS_OPEN, ACT_NONE},
        {DOORS_OPEN, ACT_NONE},
        {IDLE, ACT_CLOSE},
        {FAULT, ACT_FAULT},
        {FAULT, ACT_FAULT},
        {DOORS_OPEN, ACT_NONE}
    },
    [FAULT] = {
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {FAULT, ACT_NONE},
        {IDLE, ACT_RESET}
    }
};

void fsm_init(elevator_t *elevator, time_t now)
{
    elevator->state = IDLE;
    elevator->current_floor = 1;
    elevator->target_floor = 1;
    elevator->state_since = now;
    elevator->move_since = now;
    elevator->previous_switches = 0;
    elevator->fault_pending = false;
}

state_t fsm_transition(elevator_t *elevator,
                       event_t event, time_t now)
{
    transition_t t = table[elevator->state][event];

    switch (t.action) {
        case ACT_START:
        case ACT_MOVE:
            elevator->move_since = now;
            break;

        case ACT_PENDING:
            elevator->fault_pending = true;
            break;

        case ACT_FAULT:
        case ACT_RESET:
            elevator->fault_pending = false;
            elevator->target_floor =
                elevator->current_floor;
            break;

        case ACT_OPEN:
        case ACT_CLOSE:
        case ACT_NONE:
            break;
    }

    if (elevator->state != t.next)
        elevator->state_since = now;

    elevator->state = t.next;
    return elevator->state;
}

void fsm_step(elevator_t *elevator,
              const reading_t *reading,
              uint32_t switches)
{
    time_t now = reading->timestamp;

    uint32_t pressed =
        switches & ~elevator->previous_switches;

    elevator->previous_switches = switches;

    if (elevator->state == FAULT) {
        if (reading->temperature <= 35.0f)
            fsm_transition(elevator, EV_COOL, now);
        return;
    }

    if (reading->temperature > 40.0f) {
        fsm_transition(elevator, EV_OVERHEAT, now);

        if (elevator->state == FAULT)
            return;
    }

    switch (elevator->state) {
        case IDLE:
            for (int floor = 1; floor <= 3; floor++) {
                if (pressed & (1u << (floor - 1))) {
                    elevator->target_floor = floor;

                    if (floor > elevator->current_floor)
                        fsm_transition(elevator,
                                       EV_CALL_UP, now);
                    else if (floor < elevator->current_floor)
                        fsm_transition(elevator,
                                       EV_CALL_DOWN, now);
                    else
                        fsm_transition(elevator,
                                       EV_CALL_SAME, now);
                    break;
                }
            }
            break;

        case UP:
        case DOWN:
            if (difftime(now, elevator->move_since) >= 6) {
                if (elevator->state == UP)
                    elevator->current_floor++;
                else
                    elevator->current_floor--;

                if (elevator->fault_pending)
                    fsm_transition(elevator,
                                   EV_FAULT_STOP, now);
                else if (elevator->current_floor ==
                         elevator->target_floor)
                    fsm_transition(elevator,
                                   EV_ARRIVED, now);
                else
                    fsm_transition(elevator,
                                   EV_NEXT_FLOOR, now);
            }
            break;

        case DOORS_OPEN:
            if (difftime(now, elevator->state_since) >= 8)
                fsm_transition(elevator,
                               EV_DOOR_TIMEOUT, now);
            break;

        case FAULT:
        case STATE_COUNT:
            break;
    }
}

uint32_t fsm_leds(state_t state)
{
    switch (state) {
        case UP:
            return 0x1u;
        case DOWN:
            return 0x2u;
        case DOORS_OPEN:
        case FAULT:
            return 0x4u;
        default:
            return 0;
    }
}

uint32_t fsm_rgb(state_t state)
{
    switch (state) {
        case IDLE:
            return build_rgb_reg(1, 0, 255, 0);
        case UP:
            return build_rgb_reg(1, 0, 0, 255);
        case DOWN:
            return build_rgb_reg(1, 0, 255, 255);
        case DOORS_OPEN:
            return build_rgb_reg(1, 255, 255, 0);
        case FAULT:
            return build_rgb_reg(1, 255, 0, 0);
        default:
            return 0;
    }
}
