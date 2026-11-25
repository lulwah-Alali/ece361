#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "iom361_r4.h"
#include "sensor.h"
#include "fsm.h"
#include "store.h"
#include "aux.h"
#include "report.h"
#include "bits.h"
static uint32_t pack_status(const elevator_t *elevator)
{
    uint32_t status = 0;

    status = set_field(status, 0, 3, elevator->state);
    status = set_field(status, 3, 1, elevator->state == UP);
    status = set_field(status, 4, 1, elevator->state == DOWN);
    status = set_field(status, 5, 1,
    elevator->state == DOORS_OPEN ||
    elevator->state == FAULT);
    status = set_field(status, 6, 2, elevator->current_floor);

    return status;
}
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr,
                "Usage: %s scenario.txt [--report]\n",
                argv[0]);
        return 1;
    }

    if (argc == 3 && strcmp(argv[2], "--report") != 0) {
        fprintf(stderr, "Invalid option\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("Cannot open scenario");
        return 1;
    }

    char line[256];
    long start = 0;
    int tick;
    float temperature;
    float humidity;
    unsigned int switches;
    int have_start = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#')
            continue;

        if (sscanf(line, "start %ld", &start) == 1) {
            have_start = 1;
            break;
        }
    }

    if (!have_start) {
        fprintf(stderr, "Missing start time\n");
        fclose(file);
        return 1;
    }

    int rc = 0;
    uint32_t *base = iom361_initialize(3, 3, &rc);
    if (base == NULL || rc != 0) {
        fclose(file);
        return 1;
    }

    elevator_t elevator;

    iom361_set_display(0);
    fsm_init(&elevator, (time_t)start);
    store_t *store = store_create();
    aux_t *aux = aux_create();
    if (store == NULL || aux == NULL) {
        store_destroy(store);
        aux_destroy(aux);
        fclose(file);
        return 1;
    }
int next_tick = 0;
float last_temp = 23.5;
float last_humidity = 75.0;
unsigned int last_switches = 0;    
while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %f %f %x",
                   &tick, &temperature,
                   &humidity, &switches) == 4) {
while (next_tick <= tick) {
    if (next_tick == tick) {
        last_temp = temperature;
        last_humidity = humidity;
        last_switches = switches;
    }
            reading_t reading;

_iom361_set_sensor1(last_temp, last_humidity);
_iom361_set_switches(last_switches);

sensor_read(base, (time_t)(start + next_tick), &reading);

uint32_t actual_switches =
    iom361_readReg(base, SWITCHES_REG, &rc);

fsm_step(&elevator, &reading, actual_switches);

iom361_writeReg(base, LEDS_REG,
    fsm_leds(elevator.state), &rc);

iom361_writeReg(base, RGB_LED_REG,
    fsm_rgb(elevator.state), &rc);

            record_t record;
            record.reading = reading;
            record.state = elevator.state;
            record.status = pack_status(&elevator);

            store_insert(store, &record);
            aux_add(aux, reading.temperature);
if (argc == 2) {
    char date[32];
    const char *names[] = {
        "IDLE", "UP", "DOWN",
        "DOORS_OPEN", "FAULT"
    };

    strftime(date, sizeof(date),
             "%Y-%m-%d %H:%M:%S",
             gmtime(&reading.timestamp));

    printf("%s state=%s temp=%.1f rh=%.1f leds=0x%X status=0x%08X\n",
           date,
           names[elevator.state],
           reading.temperature,
           reading.humidity,
           fsm_leds(elevator.state),
           record.status);
}
next_tick++;
}
        }
    }
    if (argc == 3) {
        report_moving_average(store, 10);
    }
size_t hot_count = aux_count_at_or_above(aux, 40.0f);
fprintf(stderr, "Readings at or above 40.0 C: %zu\n", hot_count);

    store_destroy(store);
    aux_destroy(aux);
    fclose(file);
    return 0;
}
