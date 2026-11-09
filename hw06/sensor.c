#include "sensor.h"
#include "iom361_r4.h"
#include <math.h>

int sensor_read(uint32_t *base, time_t now, reading_t *r)
{
    if (base == NULL || r == NULL) {
        return -1;
    }

    uint32_t raw_temp = base[3] & 0xFFFFF;
    uint32_t raw_rh = base[4] & 0xFFFFF;

    float temp = ((float)raw_temp / 1048576.0f)
                 * 200.0f - 50.0f;

    float rh = ((float)raw_rh / 1048576.0f)
               * 100.0f;

    r->t = now;
    r->temp_c = roundf(temp * 10.0f) / 10.0f;
    r->rh_pct = roundf(rh * 10.0f) / 10.0f;

    return 0;
}
