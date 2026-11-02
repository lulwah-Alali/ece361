#include <stdio.h>
#include "../lock.h"

static int passed = 0;
static int failed = 0;

// Checks a transition in the lock table.
static void test_transition(state_t state, event_t event,
                            state_t expected_state,
                            action_t expected_action)
{
    action_t action = A_UNDEFINED;
    state_t next = lock_step(state, event, &action);

    if (next == expected_state && action == expected_action) {
        printf("PASS: %s + %s\n",
               state_name(state), event_name(event));
        passed++;
    } else {
        printf("FAIL: %s + %s\n",
               state_name(state), event_name(event));
        failed++;
    }
}
// Tests how characters are converted into events.
static void test_event(state_t state, char c, int expected)
{
    int result = lock_event(state, c);

    if (result == expected) {
        printf("PASS: event %c\n", c);
        passed++;
    } else {
        printf("FAIL: event %c\n", c);
        failed++;
    }
}
// Runs the transition table tests.
int main(void)
{
    test_transition(LOCKED, E_RIGHT, GOT1, A_NONE);
    test_transition(LOCKED, E_WRONG, LOCKED, A_BEEP);
    test_transition(LOCKED, E_CLOSE, LOCKED, A_NONE);
    test_transition(LOCKED, E_TIMEOUT, LOCKED, A_NONE);

    test_transition(GOT1, E_RIGHT, GOT2, A_NONE);
    test_transition(GOT1, E_WRONG, LOCKED, A_BEEP);
    test_transition(GOT1, E_CLOSE, GOT1, A_NONE);
    test_transition(GOT1, E_TIMEOUT, LOCKED, A_NONE);

    test_transition(GOT2, E_RIGHT, OPEN, A_UNLOCK);
    test_transition(GOT2, E_WRONG, LOCKED, A_BEEP);
    test_transition(GOT2, E_CLOSE, GOT2, A_NONE);
    test_transition(GOT2, E_TIMEOUT, LOCKED, A_NONE);

    test_transition(OPEN, E_RIGHT, OPEN, A_NONE);
    test_transition(OPEN, E_WRONG, OPEN, A_NONE);
    test_transition(OPEN, E_CLOSE, LOCKED, A_LOCK);
    test_transition(OPEN, E_TIMEOUT, LOCKED, A_LOCK);
    // Test correct and incorrect digits.
    test_event(LOCKED, '3', E_RIGHT);
    test_event(LOCKED, '1', E_WRONG);
    test_event(GOT1, '1', E_RIGHT);
    test_event(GOT1, '4', E_WRONG);
    test_event(GOT2, '4', E_RIGHT);
    test_event(GOT2, '3', E_WRONG);

    // Test closing, timeout, and other characters.
    test_event(OPEN, '7', E_RIGHT);
    test_event(OPEN, 'c', E_CLOSE);
    test_event(GOT1, 't', E_TIMEOUT);
    test_event(LOCKED, 'x', -1);
    printf("\n%d PASS, %d FAIL\n", passed, failed);

    return failed == 0 ? 0 : 1;
}
