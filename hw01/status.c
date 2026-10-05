#include "status.h"
#include "bits.h"

#define HEAT_POS 0
#define COOL_POS 1
#define FAN_POS 2
#define FAULT_POS 3
#define MODE_POS 4
#define MODE_WIDTH 3
#define RESERVED_POS 7
#define SETPOINT_POS 8
#define SETPOINT_WIDTH 8

status_t status_unpack(uint16_t word)
{
    status_t s;

    s.heat = get_field(word, HEAT_POS, 1);
    s.cool = get_field(word, COOL_POS, 1);
    s.fan = get_field(word, FAN_POS, 1);
    s.fault = get_field(word, FAULT_POS, 1);
    s.mode = get_field(word, MODE_POS, MODE_WIDTH);
    s.reserved = get_field(word, RESERVED_POS, 1);
    s.setpoint = sign_extend(
        get_field(word, SETPOINT_POS, SETPOINT_WIDTH),
        SETPOINT_WIDTH
    );

    return s;
}
