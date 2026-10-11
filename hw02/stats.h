#ifndef STATS_H
#define STATS_H

float stats_min(const float values[], int n);
float stats_max(const float values[], int n);
float stats_mean(const float values[], int n);

int stats_longest_run_above(
    const float values[], int n,
    float threshold, int *start
);

#endif