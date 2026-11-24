#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <time.h>

typedef struct {
    time_t timestamp;
    float temperature;
    float humidity;
} reading_t;

int sensor_read(uint32_t *base, time_t timestamp,
                reading_t *reading);

#endif
