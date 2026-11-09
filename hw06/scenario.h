#ifndef SCENARIO_H
#define SCENARIO_H

#include <stdint.h>
#include <time.h>

#define MAX_SCENARIO_LINES 1000

typedef struct {
    unsigned int tick;
    float temp_c;
    float rh_pct;
    uint32_t switches;
} scenario_line_t;

typedef struct {
    time_t start;
    scenario_line_t lines[MAX_SCENARIO_LINES];
    int count;
} scenario_t;

int scenario_load(const char *filename, scenario_t *scenario);

int scenario_at(const scenario_t *scenario,
                unsigned int tick,
                scenario_line_t *line);

#endif
