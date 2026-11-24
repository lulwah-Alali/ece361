#include "sensor.h"
#include "iom361_r4.h"
#include <math.h>

int sensor_read(uint32_t *base, time_t timestamp,
                reading_t *reading)
{
    int rc;

    if (base == NULL || reading == NULL)
        return 1;

    uint32_t raw_temp =
        iom361_readReg(base, TEMP_REG, &rc);

    if (rc != 0)
        return rc;

    uint32_t raw_hum =
        iom361_readReg(base, HUMID_REG, &rc);

    if (rc != 0)
        return rc;

    double temp = raw_temp / 1048576.0 * 200.0 - 50.0;
    double hum = raw_hum / 1048576.0 * 100.0;

    reading->timestamp = timestamp;
    reading->temperature = (float)(round(temp * 10.0) / 10.0);
    reading->humidity = (float)(round(hum * 10.0) / 10.0);

    return 0;
}
