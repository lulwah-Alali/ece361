#include "lock.h"

// State transition table
const transition_t lock_table[N_STATES][N_EVENTS] = {
    [LOCKED] = {
        [E_RIGHT]   = {GOT1, A_NONE},
        [E_WRONG]   = {LOCKED, A_BEEP},
        [E_CLOSE]   = {LOCKED, A_NONE},
        [E_TIMEOUT] = {LOCKED, A_NONE}
    },
    [GOT1] = {
        [E_RIGHT]   = {GOT2, A_NONE},
        [E_WRONG]   = {LOCKED, A_BEEP},
        [E_CLOSE]   = {GOT1, A_NONE},
        [E_TIMEOUT] = {LOCKED, A_NONE}
    },
    [GOT2] = {
        [E_RIGHT]   = {OPEN, A_UNLOCK},
        [E_WRONG]   = {LOCKED, A_BEEP},
        [E_CLOSE]   = {GOT2, A_NONE},
        [E_TIMEOUT] = {LOCKED, A_NONE}
    },
    [OPEN] = {
        [E_RIGHT]   = {OPEN, A_NONE},
        [E_WRONG]   = {OPEN, A_NONE},
        [E_CLOSE]   = {LOCKED, A_LOCK},
        [E_TIMEOUT] = {LOCKED, A_LOCK}
    }
};

// Returns the next state and action for an event.
state_t lock_step(state_t s, event_t e, action_t *action)
{
    if (s < 0 || s >= N_STATES ||
        e < 0 || e >= N_EVENTS) {
        if (action != NULL)
            *action = A_UNDEFINED;
        return s;
    }

    transition_t t = lock_table[s][e];

    if (action != NULL)
        *action = t.action;

    return t.next;
}

// Converts a character into a lock event.
int lock_event(state_t s, char c)
{
    if (c == 'c')
        return E_CLOSE;

    if (c == 't')
        return E_TIMEOUT;

    if (c < '0' || c > '9')
        return -1;

    if (s == OPEN)
        return E_RIGHT;

    if (s == LOCKED && c == '3')
        return E_RIGHT;

    if (s == GOT1 && c == '1')
        return E_RIGHT;

    if (s == GOT2 && c == '4')
        return E_RIGHT;

    return E_WRONG;
}

// Returns the name of a state.
const char *state_name(state_t s)
{
    static const char *names[] = {
        "LOCKED", "GOT1", "GOT2", "OPEN"
    };

    if (s < 0 || s >= N_STATES)
        return "?";

    return names[s];
}

// Returns the name of an event.
const char *event_name(event_t e)
{
    static const char *names[] = {
        "RIGHT", "WRONG", "CLOSE", "TIMEOUT"
    };

    if (e < 0 || e >= N_EVENTS)
        return "?";

    return names[e];
}

// Returns the name of an action.
const char *action_name(action_t a)
{
    static const char *names[] = {
        "UNDEFINED", "NONE", "UNLOCK", "LOCK", "BEEP"
    };

    if (a < 0 || a >= N_ACTIONS)
        return "?";

    return names[a];
}
