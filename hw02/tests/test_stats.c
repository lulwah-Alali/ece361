#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "../stats.h"

int main(void)
{
    float values[] = {2.0f, 5.0f, 3.0f, 7.0f, 1.0f};
    int start = -1;

    assert(stats_min(values, 5) == 1.0f);
    assert(stats_max(values, 5) == 7.0f);
    assert(fabsf(stats_mean(values, 5) - 3.6f) < 0.0001f);

    int longest = stats_longest_run_above(
        values, 5, 2.0f, &start
    );

    assert(longest == 3);
    assert(start == 1);

    float below[] = {1.0f, 2.0f, 3.0f};
    start = -1;

    assert(stats_longest_run_above(
        below, 3, 5.0f, &start
    ) == 0);
    assert(start == -1);

    printf("All stats tests passed!\n");
    return 0;
}
