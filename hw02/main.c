#include <stdio.h>
#include <stdlib.h>
#include "reading.h"
#include "stats.h"
#include "histogram.h"

#define MAX_READINGS 1000

int main(int argc, char *argv[]) {
    float threshold = 30.0f;

    if (argc > 2) {
        fprintf(stderr, "usage: %s [threshold] < readings.txt\n", argv[0]);
        return 1;
    }

    if (argc == 2) {
        char *end;
        threshold = strtof(argv[1], &end);

        if (*end != '\0') {
            fprintf(stderr, "error: threshold '%s' is not a number\n", argv[1]);
            return 1;
        }
    }
    Reading readings[MAX_READINGS];
    int skipped = 0;

    int count = reading_read(
        stdin, readings, MAX_READINGS, &skipped
    );

    printf("readings: %d\n", count);
    printf("skipped:  %d\n", skipped);

    if (count == 0) {
        printf("no readings, no summary\n");
        return 0;
    }
    float temps[MAX_READINGS];
    float hums[MAX_READINGS];

    for (int i = 0; i < count; i++) {
        temps[i] = readings[i].temperature;
        hums[i] = readings[i].humidity;
    }

    printf("temperature: min %6.1f  max %6.1f  mean %6.2f C\n",
           stats_min(temps, count),
           stats_max(temps, count),
           stats_mean(temps, count));

    printf("humidity:    min %6.1f  max %6.1f  mean %6.2f %%RH\n",
           stats_min(hums, count),
           stats_max(hums, count),
           stats_mean(hums, count));
    int start = -1;
    int best = stats_longest_run_above(
        temps, count, threshold, &start
    );

    if (best == 0) {
        printf("above %.1f C: never\n", threshold);
    } else {
        printf("above %.1f C: longest run %d readings, from tick %d to tick %d\n",
               threshold, best,
               readings[start].tick,
               readings[start + best - 1].tick);
    }

    histogram_print(temps, count);

    return 0;
}