#include <assert.h>
#include <stdio.h>
#include "../fsm.h"

int main(void)
{
    elevator_t elevator;

    fsm_init(&elevator, 1000);

    fsm_transition(&elevator, EV_CALL_UP, 1001);
    assert(elevator.state == UP);

    fsm_transition(&elevator, EV_ARRIVED, 1002);
    assert(elevator.state == DOORS_OPEN);

    printf("All FSM tests passed.\n");

    return 0;
}
