#include "stats.h"

float stats_min(const float values[], int n)
{
    float min = values[0];

    for (int i = 1; i < n; i++) {
        if (values[i] < min)
            min = values[i];
    }

    return min;
}

float stats_max(const float values[], int n)
{
    if (n == 1)
        return values[0];

    float rest = stats_max(values + 1, n - 1);

    return values[0] > rest ? values[0] : rest;
}

float stats_mean(const float values[], int n)
{
    float sum = 0.0f;

    for (int i = 0; i < n; i++)
        sum += values[i];

    return sum / n;
}

int stats_longest_run_above(
    const float values[], int n,
    float threshold, int *start)
{
    int run = 0;
    int best = 0;
    int run_start = 0;

    *start = -1;

    for (int i = 0; i < n; i++) {
        if (values[i] > threshold) {
            if (run == 0)
                run_start = i;

            run++;

            if (run > best) {
                best = run;
                *start = run_start;
            }
        } else {
            run = 0;
        }
    }

    return best;
}