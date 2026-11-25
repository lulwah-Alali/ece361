#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "../bits.h"

int main(void)
{
    assert(get_field(0xAB, 0, 4) == 0xB);
    assert(get_field(0xAB, 4, 4) == 0xA);

    assert(set_field(0, 4, 4, 0xA) == 0xA0);
    assert(set_field(0xFF, 0, 4, 0) == 0xF0);

    assert(sign_extend(0x7, 4) == 7);
    assert(sign_extend(0xF, 4) == -1);
    assert(sign_extend(0x8, 4) == -8);

    for (uint32_t state = 0; state < 5; state++) {
        for (uint32_t floor = 1; floor <= 3; floor++) {
            uint32_t status = 0;
            uint32_t up = (state == 1);
            uint32_t down = (state == 2);
            uint32_t door = (state == 3 || state == 4);

            status = set_field(status, 0, 3, state);
            status = set_field(status, 3, 1, up);
            status = set_field(status, 4, 1, down);
            status = set_field(status, 5, 1, door);
            status = set_field(status, 6, 2, floor);

            assert(get_field(status, 0, 3) == state);
            assert(get_field(status, 3, 1) == up);
            assert(get_field(status, 4, 1) == down);
            assert(get_field(status, 5, 1) == door);
            assert(get_field(status, 6, 2) == floor);

            assert((status & 0xFFFFFF00u) == 0);
        }
    }

    printf("All bits and status word tests passed.\n");

    return 0;
}
