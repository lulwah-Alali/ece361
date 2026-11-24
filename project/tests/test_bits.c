#include <assert.h>
#include <stdio.h>
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

    printf("All bits tests passed.\n");

    return 0;
}
