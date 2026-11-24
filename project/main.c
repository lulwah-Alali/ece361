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
    status = set_field(status, 5, 1, elevator->state == DOORS_OPEN);
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
    fsm_init(&elevator, (time_t)start);
    store_t *store = store_create();
    aux_t *aux = aux_create();
    if (store == NULL || aux == NULL) {
        store_destroy(store);
        aux_destroy(aux);
        fclose(file);
        return 1;
    }    
while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %f %f %x",
                   &tick, &temperature,
                   &humidity, &switches) == 4) {
            reading_t reading;
            reading.timestamp = (time_t)(start + tick);
            reading.temperature = temperature;
            reading.humidity = humidity;

            fsm_step(&elevator, &reading, switches);

            record_t record;
            record.reading = reading;
            record.state = elevator.state;
            record.status = pack_status(&elevator);

            store_insert(store, &record);
            aux_add(aux, reading.temperature);
            printf("%ld %.2f %.2f 0x%X\n",
                   start + tick,
                   temperature,
                   humidity,
                   switches);
        }
    }
    if (argc == 3) {
        report_moving_average(store, 3);
    }
    store_destroy(store);
    aux_destroy(aux);
    fclose(file);
    return 0;
}
