#ifndef READING_H
#define READING_H

#include <stdio.h>

#define MAX_READINGS 1000

typedef struct {
    int tick;
    float temperature;
    float humidity;
} Reading;

int reading_read(FILE *input, Reading readings[],
                 int max_readings, int *skipped);

#endif