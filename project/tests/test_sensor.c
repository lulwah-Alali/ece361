#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "../sensor.h"
#include "../iom361_r4.h"

uint32_t iom361_readReg(uint32_t *base,
                       uint32_t offset,
                       int *rtn_code)
{
    *rtn_code = 0;
    return base[offset / 4];
}

int main(void)
{
    uint32_t registers[32] = {0};
    reading_t reading;

    registers[HUMID_REG / 4] = 524288;

    float temperatures[] = {
        0.0f, 25.0f, 35.0f, 40.0f, 100.0f
    };

    for (int i = 0; i < 5; i++) {
        registers[TEMP_REG / 4] =
            (uint32_t)round(
                (temperatures[i] + 50.0)
                * 1048576.0 / 200.0);

        assert(sensor_read(registers, 1000,
                           &reading) == 0);

        assert(reading.timestamp == 1000);

        assert(fabs(reading.temperature -
                    temperatures[i]) < 0.01);

        assert(fabs(reading.humidity -
                    50.0) < 0.01);
    }

    assert(sensor_read(NULL, 1000,
                       &reading) != 0);

    assert(sensor_read(registers, 1000,
                       NULL) != 0);

    printf("All sensor tests passed.\n");

    return 0;
}
