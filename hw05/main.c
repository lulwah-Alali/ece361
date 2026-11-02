#include <stdio.h>
#include "lock.h"

int main(void)
{
    state_t state = LOCKED;
    state_t next;
    action_t action;
    int event;
    int c;

    while ((c = getchar()) != EOF) {
        event = lock_event(state, (char)c);

        if (event == -1)
            continue;

        next = lock_step(state, (event_t)event, &action);

        printf("%s %c %s -> %s %s\n",
               state_name(state),
               (char)c,
               event_name((event_t)event),
               state_name(next),
               action_name(action));

        state = next;
    }

    printf("STATE: %s\n", state_name(state));

    return 0;
}
