#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "iom361_r4.h"
#include "sensor.h"
#include "panel.h"
#include "scenario.h"

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "replay") != 0) {
        fprintf(stderr, "Usage: ./replay scenario.txt\n");
        return 1;
    }

    scenario_t scenario = {0};

    int rc = scenario_load(argv[2], &scenario);
    if (rc != 0) {
        fprintf(stderr, "Scenario load failed: %d\n", rc);
        return 1;
    }

    uint32_t *base = iom361_initialize(4, 4, &rc);
    if (rc != 0 || base == NULL) {
        fprintf(stderr, "Initialization failed: %d\n", rc);
        return 1;
    }

    iom361_set_display(false);

    uint32_t previous = 0;

    for (unsigned int tick = 0;
         tick <= scenario.lines[scenario.count - 1].tick;
         tick++) {

        scenario_line_t line;

        if (scenario_at(&scenario, tick, &line) != 0) {
            fprintf(stderr, "Scenario error at tick %u\n", tick);
            return 1;
        }

        _iom361_set_sensor1(line.temp_c, line.rh_pct);
        _iom361_set_switches(line.switches);

        time_t now = scenario.start + tick;
        reading_t reading;

        if (sensor_read(base, now, &reading) != 0) {
            fprintf(stderr, "Sensor read failed\n");
            return 1;
        }

        uint32_t switches =
            iom361_readReg(base, SWITCHES_REG, &rc);

        if (rc != 0) {
            fprintf(stderr, "Switch read failed\n");
            return 1;
        }

        uint32_t pressed =
            panel_pressed(switches, previous);

        for (int k = 0; k < 4; k++) {
            if (pressed & (1u << k)) {
                if (panel_toggle(base, k) != 0) {
                    fprintf(stderr, "LED toggle failed\n");
                    return 1;
                }
            }
        }

        previous = switches;

        uint32_t leds =
            iom361_readReg(base, LEDS_REG, &rc);

        if (rc != 0) {
            fprintf(stderr, "LED read failed\n");
            return 1;
        }

        char timestamp[32];
        struct tm *utc = gmtime(&now);

        if (utc == NULL ||
            strftime(timestamp, sizeof(timestamp),
                     "%Y-%m-%d %H:%M:%S", utc) == 0) {
            fprintf(stderr, "Time conversion failed\n");
            return 1;
        }

        printf("%s temp=%.1f rh=%.1f switches=0x%x "
               "pressed=0x%x leds=0x%x\n",
               timestamp,
               reading.temp_c,
               reading.rh_pct,
               switches,
               pressed,
               leds);
    }

    return 0;
}
