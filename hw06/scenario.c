#include "scenario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int scenario_load(const char *filename, scenario_t *scenario)
{
    if (filename == NULL || scenario == NULL)
        return -1;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return -1;

    scenario->count = 0;
    scenario->start = 0;

    char buffer[256];
    int line_number = 0;
    int has_start = 0;
    unsigned int previous_tick = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        line_number++;

        char *p = buffer;

        while (isspace((unsigned char)*p))
            p++;

        if (*p == '#' || *p == '\0')
            continue;

        if (!has_start) {
            char date[32], time[32];

            if (sscanf(p, "start %31s %31s", date, time) != 2) {
                fclose(file);
                return line_number;
            }

            struct tm tm_value = {0};

            if (sscanf(date, "%d-%d-%d",
                       &tm_value.tm_year,
                       &tm_value.tm_mon,
                       &tm_value.tm_mday) != 3) {
                fclose(file);
                return line_number;
            }

            tm_value.tm_year -= 1900;
            tm_value.tm_mon -= 1;

            if (sscanf(time, "%d:%d:%d",
                       &tm_value.tm_hour,
                       &tm_value.tm_min,
                       &tm_value.tm_sec) != 3) {
                fclose(file);
                return line_number;
            }

            scenario->start = timegm(&tm_value);
            has_start = 1;
            continue;
        }

        scenario_line_t line;

        if (sscanf(p, "%u %f %f %x",
                   &line.tick,
                   &line.temp_c,
                   &line.rh_pct,
                   &line.switches) != 4) {
            fclose(file);
            return line_number;
        }

        if (scenario->count >= MAX_SCENARIO_LINES ||
            (scenario->count > 0 &&
             line.tick <= previous_tick)) {
            fclose(file);
            return line_number;
        }

        scenario->lines[scenario->count++] = line;
        previous_tick = line.tick;
    }

    fclose(file);

    if (!has_start)
        return line_number + 1;

    return 0;
}

int scenario_at(const scenario_t *scenario,
                unsigned int tick,
                scenario_line_t *line)
{
    if (scenario == NULL || line == NULL ||
        scenario->count == 0)
        return -1;

    int found = -1;

    for (int i = 0; i < scenario->count; i++) {
        if (scenario->lines[i].tick <= tick)
            found = i;
        else
            break;
    }

    if (found < 0)
        return -1;

    *line = scenario->lines[found];
    return 0;
}
