#include <stdio.h>
#include <stdint.h>
#include "bits.h"
#include "status.h"

static int passed = 0;
static int failed = 0;

#define CHECK(name, condition)                  \
    do {                                        \
        if (condition) {                        \
            printf("PASS: %s\n", name);         \
            passed++;                           \
        } else {                                \
            printf("FAIL: %s\n", name);         \
            failed++;                           \
        }                                       \
    } while (0)

int main(void)
{
    /* print_binary */
    printf("print_binary 0x2C, width 8: ");
    print_binary(0x2C, 8);
    printf("  (expected 0010 1100)\n");
    CHECK("print_binary called", 1);

    /* get_field */
    CHECK("get_field basic",
          get_field(0x2C, 2, 3) == 3);

    CHECK("get_field width 1",
          get_field(0x1, 0, 1) == 1);

    CHECK("get_field width 32",
          get_field(0x12345678, 0, 32) == 0x12345678);

    CHECK("get_field pos 31",
          get_field(0x80000000, 31, 1) == 1);

    CHECK("get_field invalid range",
          get_field(0xFFFFFFFF, 31, 2) == 0);

    /* set_field */
    CHECK("set_field basic",
          set_field(0, 4, 3, 5) == 0x50);

    CHECK("set_field pos 31",
          set_field(0, 31, 1, 1) == 0x80000000);

    CHECK("set_field value too wide",
          set_field(0, 4, 3, 0xF) == 0x70);

    CHECK("set_field width 32",
          set_field(0xFFFFFFFF, 0, 32, 0x12345678)
              == 0x12345678);

    CHECK("set_field invalid range",
          set_field(0x12345678, 31, 2, 0)
              == 0x12345678);

    /* sign_extend */
    CHECK("sign_extend positive",
          sign_extend(0x7F, 8) == 127);

    CHECK("sign_extend negative",
          sign_extend(0xF8, 8) == -8);

    CHECK("sign_extend most negative",
          sign_extend(0x80, 8) == -128);

    CHECK("sign_extend width 32",
          sign_extend(0xFFFFFFFF, 32) == -1);

    /* status_unpack example from assignment */
    status_t s1 = status_unpack(0x1631);

    CHECK("status1 heat", s1.heat == 1);
    CHECK("status1 cool", s1.cool == 0);
    CHECK("status1 fan", s1.fan == 0);
    CHECK("status1 fault", s1.fault == 0);
    CHECK("status1 mode", s1.mode == 3);
    CHECK("status1 reserved", s1.reserved == 0);
    CHECK("status1 setpoint", s1.setpoint == 22);

    /* Second status word: negative setpoint and reserved bit set */
    status_t s2 = status_unpack(0xFF8E);

    CHECK("status2 heat", s2.heat == 0);
    CHECK("status2 cool", s2.cool == 1);
    CHECK("status2 fan", s2.fan == 1);
    CHECK("status2 fault", s2.fault == 1);
    CHECK("status2 mode", s2.mode == 0);
    CHECK("status2 reserved", s2.reserved == 1);
    CHECK("status2 setpoint", s2.setpoint == -1);

    /* Third status word: invalid mode 5 and minimum setpoint */
    status_t s3 = status_unpack(0x8050);

    CHECK("status3 mode invalid value", s3.mode == 5);
    CHECK("status3 reserved", s3.reserved == 0);
    CHECK("status3 setpoint", s3.setpoint == -128);

    printf("\n%d passed, %d failed\n", passed, failed);

    return failed == 0 ? 0 : 1;
}
