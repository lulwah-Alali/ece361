#include "panel.h"

uint32_t panel_pressed(uint32_t now, uint32_t before)
{
    return now & ~before;
}

uint32_t panel_released(uint32_t now, uint32_t before)
{
    return before & ~now;
}

int panel_led(uint32_t *base, int n, int on)
{
    if (n < 0 || n > 31)
        return -1;

    uint32_t mask = 1u << n;
    uint32_t leds = base[1];

    if (on)
        leds |= mask;
    else
        leds &= ~mask;

    base[1] = leds;
    return 0;
}

int panel_toggle(uint32_t *base, int n)
{
    if (n < 0 || n > 31)
        return -1;

    uint32_t mask = 1u << n;
    uint32_t leds = base[1];

    base[1] = leds ^ mask;
    return 0;
}
